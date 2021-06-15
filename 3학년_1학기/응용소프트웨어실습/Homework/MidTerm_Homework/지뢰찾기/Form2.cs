using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 지뢰찾기 {
    public partial class PlayBoard : Form {
        public DataGetEventHandler DataSendEvent;
        public Button[,] buttons;
        public int[,] aroundMine; //주변에 지뢰 몇개있는지 저장하는 변수
        public bool[,] mine_2D; //지뢰 위치 저장하는 변수
        public bool[,] isPrint; //해당 위치의 숫자 이미 출력했는지 판단하는 함수
        public bool[,] alreayPassThrough; //0 눌렀을 때 경계밝히는데 사용되는 변수
        public int fluidMineNum; //게임 종료여부 판단에서 사용되는 남아있는 지뢰의 수
        public int solidMineNum; //게임 종료여부 판단에서 각 난이도에서의 지뢰의 수 저장되는 변수(늘거나 줄지 않는다)
        public int flagNum; //사용 가능한 남은 깃발의 갯수
        int judgeNum; //solidMineNum과 비교해서 같아지면 남아있는게 지뢰뿐이므로 그걸 판단하는데 사용되는 변수
        public Random r = new Random();

        private int x;
        private int y;
        private int mineNum;

        public PlayBoard(int x, int y, int mineNum) {
            this.x = x;
            this.y = y;
            this.mineNum = mineNum;

            if (x == 9) {
                initialize(9);
            } else if (x == 16 && y == 16) {
                initialize(16);
            } else if (x == 16 && y == 30) {
                initialize(30);
            }

            InitializeComponent();
        }

        //난이도에 따라 각 변수들 초기화해주는 함수.
        public void initialize(int widthNum) {
            if (widthNum == 9) { //난이도가 초급일 때
                fluidMineNum = 10;
                flagNum = 10;
                solidMineNum = 10;
                judgeNum = 80;
                buttons = new Button[9, 9];
                aroundMine = new int[9, 9];
                isPrint = new bool[9, 9];
                mine_2D = new bool[9, 9];
                alreayPassThrough = new bool[9, 9];
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        buttons[i, j] = new System.Windows.Forms.Button();
                        buttons[i, j].Location = new Point(30 * j, 30 * i);
                        buttons[i, j].Size = new Size(28, 28);
                        buttons[i, j].Text = null;
                        buttons[i, j].Name = String.Format("{0}-{1} ", i, j);
                        buttons[i, j].MouseDown += new MouseEventHandler(this.btn_Click);
                        this.Controls.Add(buttons[i, j]); //버튼 동적으로 생성
                        aroundMine[i, j] = 0;
                        mine_2D[i, j] = false;
                        isPrint[i, j] = false;
                        alreayPassThrough[i, j] = false;
                    }
                }

                for (int a = 0; a < 10; a++) { //지뢰 랜덤으로 생성하는 함수
                    int i = r.Next(0, 9);
                    int j = r.Next(0, 9);

                    if (mine_2D[i, j] == true) { //이미 지뢰가 설치된 곳이면 a값을 줄여서 다시 생성
                        a--;
                        continue;
                    } else if (mine_2D[i, j] == false) { //지뢰가 생성되지 않은 곳이면
                        mine_2D[i, j] = true;
                        aroundMine[i, j] = -100;

                        for (int x = -1; x <= 1; x++) { //지뢰 생성된 곳 주변의 칸들 중 지뢰가 없고 칸이 인덱스에서 벗어나지 않는 곳에 aroundMine값 증가
                            for (int y = -1; y <= 1; y++) {
                                if (x == 0 && y == 0)
                                    continue;
                                else if (i + x < 0 || i + x > 8 || j + y < 0 || j + y > 8)
                                    continue;
                                else if (mine_2D[i + x, j + y] == true)
                                    continue;
                                else
                                    aroundMine[i + x, j + y]++;
                            }
                        }
                    }
                }
            } else if(widthNum == 16) { //난이도가 중급일 때 초기화
                fluidMineNum = 40;
                flagNum = 40;
                solidMineNum = 40;
                judgeNum = 255;
                buttons = new Button[16, 16];
                aroundMine = new int[16, 16];
                isPrint = new bool[16, 16];
                mine_2D = new bool[16, 16];
                alreayPassThrough = new bool[16, 16];
                for (int i = 0; i < 16; i++) {
                    for (int j = 0; j < 16; j++) {
                        buttons[i, j] = new System.Windows.Forms.Button();
                        buttons[i, j].Location = new Point(30 * j, 30 * i);
                        buttons[i, j].Size = new Size(28, 28);
                        buttons[i, j].Text = null;
                        buttons[i, j].Name = String.Format("{0}-{1} ", i, j);
                        buttons[i, j].MouseDown += new MouseEventHandler(this.btn_Click);
                        this.Controls.Add(buttons[i, j]);
                        aroundMine[i, j] = 0;
                        mine_2D[i, j] = false;
                        isPrint[i, j] = false;
                        alreayPassThrough[i, j] = false;
                    }
                }

                for (int a = 0; a < 40; a++) {
                    int i = r.Next(0, 16);
                    int j = r.Next(0, 16);

                    if (mine_2D[i, j] == true) {
                        a--;
                        continue;
                    } else if (mine_2D[i, j] == false) {
                        mine_2D[i, j] = true;
                        aroundMine[i, j] = -100;

                        for (int x = -1; x <= 1; x++) {
                            for (int y = -1; y <= 1; y++) {
                                if (x == 0 && y == 0)
                                    continue;
                                else if (i + x < 0 || i + x > 15 || j + y < 0 || j + y > 15)
                                    continue;
                                else if (mine_2D[i + x, j + y] == true)
                                    continue;
                                else
                                    aroundMine[i + x, j + y]++;
                            }
                        }
                    }
                }
            } else if(widthNum == 30) { //난이도가 고급일 때
                fluidMineNum = 99;
                flagNum = 99;
                solidMineNum = 99;
                judgeNum = 479;
                buttons = new Button[16, 30];
                aroundMine = new int[16, 30];
                isPrint = new bool[16, 30];
                mine_2D = new bool[16, 30];
                alreayPassThrough = new bool[16, 30];
                for (int i = 0; i < 16; i++) {
                    for (int j = 0; j < 30; j++) {
                        buttons[i, j] = new System.Windows.Forms.Button();
                        buttons[i, j].Location = new Point(30 * j, 30 * i);
                        buttons[i, j].Size = new Size(28, 28);
                        buttons[i, j].Text = null;
                        buttons[i, j].Name = String.Format("{0}-{1} ", i, j);
                        buttons[i, j].MouseDown += new MouseEventHandler(this.btn_Click);
                        this.Controls.Add(buttons[i, j]);
                        aroundMine[i, j] = 0;
                        mine_2D[i, j] = false;
                        isPrint[i, j] = false;
                        alreayPassThrough[i, j] = false;
                    }
                }

                for (int a = 0; a < 99; a++) {
                    int i = r.Next(0, 16);
                    int j = r.Next(0, 30);

                    if (mine_2D[i, j] == true) {
                        a--;
                        continue;
                    } else if (mine_2D[i, j] == false) {
                        mine_2D[i, j] = true;
                        aroundMine[i, j] = -100;

                        for (int x = -1; x <= 1; x++) {
                            for (int y = -1; y <= 1; y++) {
                                if (x == 0 && y == 0)
                                    continue;
                                else if (i + x < 0 || i + x > 15 || j + y < 0 || j + y > 29)
                                    continue;
                                else if (mine_2D[i + x, j + y] == true)
                                    continue;
                                else
                                    aroundMine[i + x, j + y]++;
                            }
                        }
                    }
                }
            }
        }

        //동적으로 생성된 버튼들이 클릭되었을 때 발생하는 메소드
        public void btn_Click(object sender, MouseEventArgs e) {
            string name = ((Button)sender).Name; //버튼 생성시 버튼의 이름을 0행 0열이면 0-0 이런식으로 저장했는데 이걸 가져온다.
            char sp = '-';

            string[] temp = name.Split(sp); //이름을 -를 기준으로 앞뒤로 자른다.

            int i = 0, j = 0;

            i = Int32.Parse(temp[0]); //이름 자른 것 중 앞이 행, 뒤가 열이 된다.
            j = Int32.Parse(temp[1]);

            Size size = this.Size;

            int row = 0;
            int column = 0;

            //생성되어있는 PlayBoard의 사이즈를 기준으로 선택된 게임의 난이도를 판단해 row, column값을 구해줌.
            if (size.Width > 250 && size.Width < 350) {
                row = 9;
                column = 9;
            } else if (size.Width > 350 && size.Width < 600) {
                row = 16;
                column = 16;
            } else {
                row = 16;
                column = 30;
            }

            if (e.Button == MouseButtons.Left) { //마우스 왼쪽 버튼 눌렸을 때
                if (mine_2D[i, j] == true) { //좌클릭으로 지뢰 클릭하면 지뢰가 있는 곳은 지뢰 표시해주고 아닌 곳은 주변 지뢰 몇개였는지 숫자로 출력
                    for (int x = 0; x < row; x++) {
                        for (int y = 0; y < column; y++) {
                            if (mine_2D[x, y] == true)
                                buttons[x, y].Text = "●";
                            else {
                                buttons[x, y].Text = aroundMine[x, y].ToString();
                            }
                        }
                    }
                    DataSendEvent("lose"); //마지막에 lose 데이터 전달해줌.
                } else { //좌클릭으로 지뢰 말고 다른거 클릭
                    if (judgeNum == solidMineNum) { //판단하는 변수인 judgeNum과 고정된 지뢰 갯수인 solidNum이 같으면 남은게 다 지뢰이므로 승리
                        buttons[i, j].Text = aroundMine[i, j].ToString();
                        for (int a = 0; a < row; a++) {
                            for (int b = 0; b < column; b++) {
                                if (mine_2D[a, b] == true)
                                    buttons[a, b].Text = "●";
                            }
                        }
                        DataSendEvent("win");
                    } else if (aroundMine[i, j] > 0 && isPrint[i, j] == false) { //클릭한 버튼에 저장된 aroundMine값이 0보다 크고 아직 출력하지 않은 것이라면
                        buttons[i, j].Text = aroundMine[i, j].ToString();
                        isPrint[i, j] = true;
                        judgeNum--;
                    } else if (aroundMine[i, j] == 0 && isPrint[i, j] == false && alreayPassThrough[i, j] == false) { //왼쪽 클릭했는데 0이고 아직 출력 안했고 alreadyPassThrouhgh도 false라면
                        PrintBoundary(i, j, row, column); //경계밝히기 함수를 실행한다.
                    }
                }
            } else if (e.Button == MouseButtons.Right) { //마우스 오른쪽 버튼을 클릭했을 경우
                if (buttons[i, j].Text == "▶") { //버튼에 이미 깃발이 있던 경우
                    buttons[i, j].Text = "";
                    flagNum++;
                    isPrint[i, j] = false;
                    alreayPassThrough[i, j] = false;
                    if (mine_2D[i, j] == true) //깃발이 꽂혀 있던 곳의 깃발을 제거했는데 지뢰가 있던 곳이면
                        fluidMineNum++; //남아있는 지뢰 갯수 판단하는 fluidMineNum을 증가시킴
                } else if (flagNum > 0) { //깃발이 다 안 꽂혔을 경우에만 깃발을 꽂을 수 있다.
                    buttons[i, j].Text = "▶";
                    flagNum--;
                    isPrint[i, j] = true;

                    if (mine_2D[i, j] == true) //깃발 꽂은 곳에 지뢰가 있었다면 남아있는 지뢰 개수를 줄여준다.
                        fluidMineNum--;

                    if (flagNum == 0 && fluidMineNum == 0) { //깃발도 다 쓰고 남아있는 지뢰의 개수도 0개라면 win 데이터를 보내준다.
                        DataSendEvent("win");
                    }
                }
            }
        }

        //0 클릭했을 경우 경계밝혀주는 함수이다.
        public void PrintBoundary(int i, int j, int row, int column) {
            if (judgeNum == solidMineNum) { //경계 밝혀주다가 만일 남아있는 지뢰 갯수와 칸이 같으면 win 데이터 전송
                buttons[i, j].Text = aroundMine[i, j].ToString();
                for (int a = 0; a < row; a++) {
                    for (int b = 0; b < column; b++) {
                        if (mine_2D[a, b] == true)
                            buttons[a, b].Text = "●";
                    }
                }
                DataSendEvent("win");
            }

            //0을 클릭했을 경우는 자기 자신의 text가 아직 출력되지 않았을 경우 출력을 우선 하고 주변의 8칸을 출력하게 된다.
            //그런데 주변의 숫자 중 0이 있을 수 있는데 이 0에서 이미 주변까지 출력을 다 했다면 이 칸에서는 출력을 하면 안 된다.
            //그래서 0에서 이미 주변을 다 출력했다고 판단을 할 때 사용해주는 변수를 alreayPassThrough라고 했고 이게 true면 그냥 종료하게 된다.
            if (alreayPassThrough[i, j] == true) 
                return;

            string[] temp = new string[8];
            int num = 0;
            for (int a = 0; a < 8; a++)
                temp[a] = null;

            if (isPrint[i, j] == false && aroundMine[i, j] == 0) { //클릭된 곳이 아직 출력이 안되었고 0이라면
                isPrint[i, j] = true;
                buttons[i, j].Text = aroundMine[i, j].ToString();
                judgeNum--;
                alreayPassThrough[i, j] = true; //이 값을 바꿔 줌으로써 여기선 주변의 값을 이미 출력했다고 해준다.
            } else if (isPrint[i, j] == true && aroundMine[i, j] == 0) //출력도 했고 값이 0이라면 이미 지난 곳으로 판단해서 alreadyPassThrough를 true로
                alreayPassThrough[i, j] = true;
            
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0)
                        continue;
                    else if (i + x < 0 || i + x > (row - 1) || j + y < 0 || j + y > (column - 1)) //해당 칸이 인덱스에서 벗어난 경우는 continue
                        continue;
                    else if (isPrint[i + x, j + y] == true && aroundMine[i + x, j + y] > 0) //이미 출력했고 값이 0보다 크면 continue
                        continue;
                    else if (isPrint[i + x, j + y] == false && aroundMine[i + x, j + y] > 0) { //아직 출력 안 했고 0보다 크면 출력, isPrint를 true, judgeNum 줄여주고 continue
                        buttons[i + x, j + y].Text = aroundMine[i + x, j + y].ToString();
                        isPrint[i + x, j + y] = true;
                        judgeNum--;
                        continue;
                    } else if (aroundMine[i + x, j + y] == 0 && alreayPassThrough[i + x, j + y] == true) { //값은 0인데 alreadyPassThrough가 true면 이미 지난 곳이므로 continue
                        continue;
                    } else if (aroundMine[i + x, j + y] == 0 && alreayPassThrough[i + x, j + y] == false) { //값이 0이고 alreadyPassThrough가 false면 아직 안 지난 곳이다.
                        int tempI = i + x;
                        int tempJ = j + y;
                        string stringIndex = tempI + "-" + tempJ;
                        temp[num++] = stringIndex; //0이고 아직 alreadyPassThrough가 0이면 현재 칸에서 출력을 다 끝내고 [i+x, j+y]인덱스에 가서 PrintBoundary를 호출하게 된다.
                    }
                }
            }

            for (int k = 0; k < num; k++) { //PrintBoundary를 하기 위해 선언한 변수인 num의 개수에 따라서 PrintBoundary를 또 다시 호출하게 된다.
                char sp = '-';

                string[] seperation = temp[k].Split(sp); //저장할 때 -를 붙여서 저장했으니 -를 기준으로 split을 해준다.

                int x = 0, y = 0;

                x = Int32.Parse(seperation[0]);
                y = Int32.Parse(seperation[1]);

                PrintBoundary(x, y, row, column); //출력할 곳의 좌표인 x, y와 현재 난이도의 행과 열을 나타내는 row, column을 넘겨준다.
            }
        }

        private void PlayBoard_FormClosing(object sender, FormClosingEventArgs e) {
            Environment.Exit(0);
            System.Diagnostics.Process.GetCurrentProcess().Kill();
            this.Close();
        }
    }
}
