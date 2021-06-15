using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RogueLikeGame {
    public partial class Form1 : Form {
        private Random r = new Random();
        private int stageNum;
        private int portalNum;
        private int monsterNum;
        private int row;
        private int column;
        private Label stageLabel;
        private Label lifeLabel;
        private Label[,] labels;
        private Portal[] portal;
        private Monster[] monster;
        private int finalStage;
        private int[] exitLocation = new int[2];
        private Stage[] stage;
        private bool[,] isPortal;
        private bool[,] isMonster;
        private int[] player;
        private int presentStage;
        private int[,] connectArr;
        
        private int life = 5;

        public Form1() {
            InitializeComponent();
        }

        public void initialize() {
            stageNum = r.Next(2, 11); //스테이지 갯수
            finalStage = r.Next(1, stageNum); //최종 스테이지는 어딘지
            stage = new Stage[stageNum];
            connectArr = new int[stageNum, stageNum];

            while (true) {
                for (int i = 0; i < stageNum; i++) {
                    for (int j = 0; j < stageNum; j++)
                        connectArr[i, j] = 0;
                }

                for (int i = 0; i < stageNum; i++) {
                    int number = 0;
                    for (int j = 0; j < stageNum; j++) {
                        if (connectArr[i, j] == 1)
                            number++;
                    }
                    for (int j = i + 1; j < stageNum; j++) {
                        int a = r.Next(0, 2);

                        if (number == 4)
                            break;

                        if (a == 1)
                            number++;

                        connectArr[i, j] = a;
                        connectArr[j, i] = a;
                    }
                    if (number == 0) {
                        while (true) {
                            int b = r.Next(0, stageNum);

                            if (b != i) {
                                connectArr[i, b] = 1;
                                connectArr[b, i] = 1;
                                break;
                            }
                        }
                    }
                }

                bool over4 = false;

                for(int i = 0; i < stageNum; i++) { //한 스테이지에 포탈이 4개 넘게 있을 경우 포탈 다시 만듦
                    int temp = 0;
                    for(int j = 0; j < stageNum; j++) {
                        if (connectArr[i, j] == 1)
                            temp++;
                    }
                    if(temp > 4) {
                        over4 = true;
                        break;
                    }
                }

                if (over4)
                    continue;

                bool existpath = PathExist();

                if(existpath) //스테이지에 포탈이 4개 이하이고 최종경로로 가는 길이 있으면 빠져나간다.
                    break;
            }


            //이 아래에 주석처리 되어 있는 부분으로 최종 스테이지와 스테이지별 연결 여부를 확인할 수 있다.
            /*string str = "";

            for(int i = 0; i < stageNum; i++) {
                for(int j = 0; j < stageNum; j++) {
                    str += connectArr[i, j].ToString() + "  ";
                }
                str += "\r\n";
            }

            MessageBox.Show("finalStage: " + finalStage.ToString() + "\r\n\r\n" + str);*/


            for (int i = 0; i < stageNum; i++) {
                row = r.Next(3, 21); //스테이지 가로
                column = r.Next(3, 21); //스테이지 세로

                int col = 0;
                for(int a = 0; a < stageNum; a++) {
                    if (connectArr[i, a] == 1)
                        col++;
                }

                portal = new Portal[col];

                monsterNum = r.Next(0, ((row * column) / 5) + 1); //스테이지마다 몬스터 개수
                monster = new Monster[monsterNum];

                isPortal = new bool[row, column]; //포탈이 설치되어 있는지
                isMonster = new bool[row, column];

                for (int x = 0; x < row; x++) {
                    for (int y = 0; y < column; y++) {
                        isPortal[x, y] = false;
                        isMonster[x, y] = false;
                    }
                }

                int index = 0;

                for (int j = 0; j < col; j++) { //포탈 위치 정하기
                    int a = r.Next(0, row);
                    int b = r.Next(0, column);

                    if (isPortal[a, b] == true) {
                        j--;
                        continue;
                    } else {
                        portal[j] = new Portal();
                        portal[j].setLocation(a, b);

                        while(connectArr[i, index] != 1) {
                            index++;
                        }
                        portal[j].setConnectStage(index);
                        index++;

                        isPortal[a, b] = true;
                    }
                }

                if (finalStage == i) { //finalStage에서는 탈출 포탈을 하나 더 생성한다.
                    while (true) {
                        int a = r.Next(0, row);
                        int b = r.Next(0, column);

                        if (isPortal[a, b] == true)
                            continue;
                        else {
                            exitLocation[0] = a;
                            exitLocation[1] = b;
                            isPortal[a, b] = true;
                            break;
                        }
                    }
                }

                for (int j = 0; j < monsterNum; j++) { //몬스터 위치 정하기
                    int a = r.Next(0, row);
                    int b = r.Next(0, column);

                    if (isPortal[a, b] == true || isMonster[a, b] == true) {
                        j--;
                        continue;
                    } else {
                        monster[j] = new Monster();
                        monster[j].setLocation(a, b);
                        isMonster[a, b] = true;
                    }
                }

                stage[i] = new Stage();
                stage[i].setRow(row);
                stage[i].setColumn(column);
                stage[i].setPortal(portal);
                stage[i].setMonster(monster);
            }
        }

        public bool PathExist() {
            Queue<int> queue = new Queue<int>();
            int connectNum = 0;

            queue.Enqueue(0);

            for (int i = 1; i < stageNum; i++) {
                connectNum = queue.Count;

                if (connectNum == 0) {
                    break;
                } else if (connectNum > 0) {
                    while (connectNum > 0) {
                        int temp = queue.Dequeue();

                        if (connectArr[temp, finalStage] == 1)
                            return true;

                        for (int b = 0; b < stageNum; b++) {
                            if (connectArr[temp, b] == 1) {
                                queue.Enqueue(i);
                            }
                        }
                        connectNum--;
                    }
                }
            }           

            return false;
        }

        private void Form1_Shown(object sender, EventArgs e) {
            initialize();

            row = stage[0].getRow();
            column = stage[0].getColumn();
            monster = new Monster[stage[0].getMonster().Length];
            monster = stage[0].getMonster();
            monsterNum = monster.Length;
            portal = new Portal[stage[0].getPortal().Length];
            portal = stage[0].getPortal();
            portalNum = portal.Length;

            presentStage = 0;

            isPortal = new bool[row, column];
            isMonster = new bool[row, column];

            for (int x = 0; x < row; x++) {
                for (int y = 0; y < column; y++) {
                    isPortal[x, y] = false;
                    isMonster[x, y] = false;
                }
            }

            this.Size = new Size(30 * (column + 1), 30 * (row + 4));

            labels = new Label[row, column];

            for (int x = 0; x < row; x++) {
                for (int y = 0; y < column; y++) {
                    labels[x, y] = new System.Windows.Forms.Label();
                    labels[x, y].Location = new System.Drawing.Point(10 + 30 * y, 10 + 30 * x);
                    labels[x, y].Text = "□";
                    labels[x, y].Font = new Font("맑은고딕", 17);
                    labels[x, y].AutoSize = true;
                    this.Controls.Add(labels[x, y]);
                }
            }

            for (int i = 0; i < monsterNum; i++) {
                int[] location = monster[i].getLocation();
                int a = location[0];
                int b = location[1];
                labels[a, b].Text = "∑";
                labels[a, b].Font = new Font("맑은고딕", 14);
                isMonster[a, b] = true;
            }

            for (int i = 0; i < portalNum; i++) {
                int[] location = portal[i].getLocation();
                int a = location[0];
                int b = location[1];
                labels[a, b].Text = "●";
                labels[a, b].Font = new Font("맑은고딕", 20);
                isPortal[a, b] = true;
            }

            player = new int[2];
            while (true) {
                int a = r.Next(0, row);
                int b = r.Next(0, column);

                if (isMonster[a, b] == false && isPortal[a, b] == false) {
                    player[0] = a;
                    player[1] = b;
                    labels[a, b].Text = "■";
                    break;
                }
            }

            stageLabel = new System.Windows.Forms.Label();
            stageLabel.Location = new Point((this.Width / 2) - 40, this.Height - 95);
            stageLabel.Text = "Stage : 0";
            stageLabel.Font = new Font("맑은고딕", 12);
            this.Controls.Add(stageLabel);

            lifeLabel = new System.Windows.Forms.Label();
            lifeLabel.Location = new Point((this.Width) / 2 - 40, this.Height - 65);
            lifeLabel.Text = "Life : 5";
            lifeLabel.Font = new Font("맑은고딕", 12);
            this.Controls.Add(lifeLabel);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e) {
            Environment.Exit(0);
            System.Diagnostics.Process.GetCurrentProcess().Kill();
            this.Close();
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e) {
            int a = player[0];
            int b = player[1];
            
            if (e.KeyCode == Keys.Up && a > 0 && isMonster[a - 1, b] == false) {
                labels[a, b].Text = "□";
                labels[a - 1, b].Text = "■";
                player[0]--;

                if (presentStage == finalStage && player[0] == exitLocation[0] && player[1] == exitLocation[1]) {
                    CreateForm2("win");
                } else if (isPortal[player[0], player[1]]) {
                    for(int i = 0; i < portalNum; i++) {
                        int[] temp = portal[i].getLocation();
                        
                        if(temp[0] == player[0] && temp[1] == player[1]) {
                            int k = portal[i].getConnectStage();
                            stage[presentStage].setPortal(portal);
                            stage[presentStage].setMonster(monster);
                            moveStage(k);

                            return;
                        }
                    }
                } else {
                    MoveMonster();
                }
            } else if (e.KeyCode == Keys.Down && a < row - 1 && isMonster[a + 1, b] == false) {
                labels[a, b].Text = "□";
                labels[a + 1, b].Text = "■";
                player[0]++;

                if(presentStage == finalStage && player[0] == exitLocation[0] && player[1] == exitLocation[1]) {
                    CreateForm2("win");
                } else if (isPortal[player[0], player[1]]) {
                    for (int i = 0; i < portalNum; i++) {
                        int[] temp = portal[i].getLocation();

                        if (temp[0] == player[0] && temp[1] == player[1]) {
                            int k = portal[i].getConnectStage();
                            stage[presentStage].setPortal(portal);
                            stage[presentStage].setMonster(monster);
                            moveStage(k);

                            return;
                        }
                    }
                } else {
                    MoveMonster();
                }
            } else if (e.KeyCode == Keys.Left && b > 0 && isMonster[a, b - 1] == false) {
                labels[a, b].Text = "□";
                labels[a, b - 1].Text = "■";
                player[1]--;

                if (presentStage == finalStage && player[0] == exitLocation[0] && player[1] == exitLocation[1]) {
                    CreateForm2("win");
                } else if (isPortal[player[0], player[1]]) {
                    for (int i = 0; i < portalNum; i++) {
                        int[] temp = portal[i].getLocation();

                        if (temp[0] == player[0] && temp[1] == player[1]) {
                            int k = portal[i].getConnectStage();
                            stage[presentStage].setPortal(portal);
                            stage[presentStage].setMonster(monster);
                            moveStage(k);

                            return;
                        }
                    }
                } else {
                    MoveMonster();
                }
            } else if (e.KeyCode == Keys.Right && b < column - 1 && isMonster[a, b + 1] == false) {
                labels[a, b].Text = "□";
                labels[a, b + 1].Text = "■";
                player[1]++;

                if (presentStage == finalStage && player[0] == exitLocation[0] && player[1] == exitLocation[1]) {
                    CreateForm2("win");
                } else if (isPortal[player[0], player[1]]) {
                    for (int i = 0; i < portalNum; i++) {
                        int[] temp = portal[i].getLocation();

                        if (temp[0] == player[0] && temp[1] == player[1]) {
                            int k = portal[i].getConnectStage();
                            stage[presentStage].setPortal(portal);
                            stage[presentStage].setMonster(monster);
                            moveStage(k);

                            return;
                        }
                    }
                } else {
                    MoveMonster();
                }
            }
        }

        public void moveStage(int num) { //이 함수 호출하기 전에 이전 스테이지의 내용은 저장해놓았다.
            for(int i = 0; i < row; i++) {
                for(int j = 0; j < column; j++) {
                    this.Controls.Remove(labels[i, j]);                    
                }
            }
            this.Controls.Remove(lifeLabel);
            this.Controls.Remove(stageLabel);

            int preStage = presentStage;
            int portalRow = 0;
            int portalColumn = 0;

            row = stage[num].getRow();
            column = stage[num].getColumn();
            monster = new Monster[stage[num].getMonster().Length];
            portal = new Portal[stage[num].getPortal().Length];
            portal = stage[num].getPortal();
            monster = stage[num].getMonster();

            portalNum = portal.Length;
            monsterNum = monster.Length;

            presentStage = num;

            isPortal = new bool[row, column];
            isMonster = new bool[row, column];
                        

            for (int x = 0; x < row; x++) {
                for (int y = 0; y < column; y++) {
                    isPortal[x, y] = false;
                    isMonster[x, y] = false;
                }
            }

            this.Size = new Size(30 * (column + 1), 30 * (row + 4));

            labels = new Label[row, column];

            for (int x = 0; x < row; x++) {
                for (int y = 0; y < column; y++) {
                    labels[x, y] = new System.Windows.Forms.Label();
                    labels[x, y].Location = new System.Drawing.Point(10 + 30 * y, 10 + 30 * x);
                    labels[x, y].Text = "□";
                    labels[x, y].Font = new Font("맑은고딕", 17);
                    labels[x, y].AutoSize = true;
                    this.Controls.Add(labels[x, y]);
                }
            }

            for (int i = 0; i < monsterNum; i++) {
                int[] location = monster[i].getLocation();
                int a = location[0];
                int b = location[1];
                labels[a, b].Text = "∑";
                labels[a, b].Font = new Font("맑은고딕", 14);
                isMonster[a, b] = true;
            }

            for (int i = 0; i < portalNum; i++) {
                int[] location = portal[i].getLocation();
                int a = location[0];
                int b = location[1];
                int connectstage = portal[i].getConnectStage();
                if(connectstage == preStage) {
                    portalRow = location[0];
                    portalColumn = location[1];
                }

                labels[a, b].Text = "●";
                labels[a, b].Font = new Font("맑은고딕", 20);
                isPortal[a, b] = true;
            }

            if(presentStage == finalStage) {
                isPortal[exitLocation[0], exitLocation[1]] = true;
                labels[exitLocation[0], exitLocation[1]].Text = "◎";
                labels[exitLocation[0], exitLocation[1]].Font = new Font("맑은고딕", 20);
            }

            player = new int[2];
            int[] decide = new int[4];

            for (int i = 0; i < 4; i++)
                decide[i] = 0;

            while (true) {
                int a = r.Next(1, 5);

                bool again = false;

                if (decide[3] > 0) {
                    MessageBox.Show("player를 놓을 위치가 없습니다");

                    Environment.Exit(0);
                    System.Diagnostics.Process.GetCurrentProcess().Kill();
                    this.Close();
                }

                for(int i = 0; i < 4; i++) {
                    if (a == decide[i])
                        again = true;
                }

                if (again)
                    continue;

                if (a == 1) {
                    if(portalRow > 0 && isMonster[portalRow - 1, portalColumn] == false && isPortal[portalRow - 1, portalColumn] == false) {
                        labels[portalRow - 1, portalColumn].Text = "■";
                        player[0] = portalRow - 1;
                        player[1] = portalColumn;
                        break;
                    } else {
                        for(int j = 0; j < 4; j++) {
                            if(decide[j] == 0) {
                                decide[j] = a;
                                break;
                            }
                        }
                        continue;
                    }
                } else if(a == 2) {
                    if (portalColumn < column - 1 && isMonster[portalRow, portalColumn + 1] == false && isPortal[portalRow, portalColumn + 1] == false) {
                        labels[portalRow, portalColumn + 1].Text = "■";
                        player[0] = portalRow;
                        player[1] = portalColumn + 1;
                        break;
                    } else {
                        for (int j = 0; j < 4; j++) {
                            if (decide[j] == 0) {
                                decide[j] = a;
                                break;
                            }
                        }
                        continue;
                    }
                } else if(a == 3) {
                    if (portalRow < row - 1 && isMonster[portalRow + 1, portalColumn] == false && isPortal[portalRow + 1, portalColumn] == false) {
                        labels[portalRow + 1, portalColumn].Text = "■";
                        player[0] = portalRow + 1;
                        player[1] = portalColumn;
                        break;
                    } else {
                        for (int j = 0; j < 4; j++) {
                            if (decide[j] == 0) {
                                decide[j] = a;
                                break;
                            }
                        }
                        continue;
                    }
                } else if(a == 4) {
                    if (portalColumn > 0 && isMonster[portalRow, portalColumn - 1] == false && isPortal[portalRow, portalColumn - 1] == false) {
                        labels[portalRow, portalColumn - 1].Text = "■";
                        player[0] = portalRow;
                        player[1] = portalColumn - 1;
                        break;
                    } else {
                        for (int j = 0; j < 4; j++) {
                            if (decide[j] == 0) {
                                decide[j] = a;
                                break;
                            }
                        }
                        continue;
                    }
                }
            }

            stageLabel = new System.Windows.Forms.Label();
            stageLabel.Location = new Point((this.Width / 2) - 40, this.Height - 95);
            stageLabel.Text = "Stage : " + presentStage.ToString();
            stageLabel.Font = new Font("맑은고딕", 12);
            this.Controls.Add(stageLabel);

            lifeLabel = new System.Windows.Forms.Label();
            lifeLabel.Location = new Point((this.Width) / 2 - 40, this.Height - 65);
            lifeLabel.Text = "Life : " + life.ToString();
            lifeLabel.Font = new Font("맑은고딕", 12);
            this.Controls.Add(lifeLabel);
        }

        public void MoveMonster() {
            int[,] cantMove = new int[monsterNum, 8];

            for(int i = 0; i < monsterNum; i++) {
                for(int j = 0; j < 8; j++) {
                    cantMove[i, j] = 0;
                }
            }

            for (int i = 0; i < monsterNum; i++) {
                if (cantMove[i, 7] > 0)
                    continue;

                if (life == 0)
                    CreateForm2("lose");

                int rand = r.Next(1, 9);
                bool decide = false;

                for (int j = 0; j < 8; j++) {
                    if (rand == cantMove[i, j]) {
                        decide = true;
                        break;
                    }
                }

                if (decide) {
                    i--;
                    continue;
                }

                int[] location = monster[i].getLocation();
                int a = location[0];
                int b = location[1];

                if (rand == 1 && a > 0 && isPortal[a - 1, b] == false && isMonster[a - 1, b] == false) { //상
                    if (player[0] == a - 1 && player[1] == b) {
                        life--;
                        lifeLabel.Text = "Life : " + life.ToString();
                    } else {
                        labels[a, b].Text = "□";
                        labels[a, b].Font = new Font("맑은고딕", 17);
                        isMonster[a, b] = false;
                        labels[a - 1, b].Text = "∑";
                        labels[a - 1, b].Font = new Font("맑은고딕", 14);
                        isMonster[a - 1, b] = true;
                        monster[i].setLocation(a - 1, b);
                    }
                    continue;
                } else if (rand == 1) {
                    if (a == 0 || isPortal[a - 1, b] == true || isMonster[a - 1, b] == true) {
                        for(int j = 0; j < 8; j++) {
                            if(cantMove[i, j] == 0) {
                                cantMove[i, j] = 1;
                                break;
                            }
                        }
                    }
                }

                if (rand == 2 && a > 0 && b < column - 1 && isPortal[a - 1, b + 1] == false && isMonster[a - 1, b + 1] == false) { //우상
                    if (player[0] == a - 1 && player[1] == b + 1) {
                        life--;
                        lifeLabel.Text = "Life : " + life.ToString();
                    } else {
                        labels[a, b].Text = "□";
                        labels[a, b].Font = new Font("맑은고딕", 17);
                        isMonster[a, b] = false;
                        labels[a - 1, b + 1].Text = "∑";
                        labels[a - 1, b + 1].Font = new Font("맑은고딕", 14);
                        isMonster[a - 1, b + 1] = true;
                        monster[i].setLocation(a - 1, b + 1);
                    }
                    continue;
                } else if (rand == 2) {
                    if (a == 0 || b == column - 1 || isPortal[a - 1, b + 1] == true || isMonster[a - 1, b + 1] == true) {
                        for (int j = 0; j < 8; j++) {
                            if (cantMove[i, j] == 0) {
                                cantMove[i, j] = 2;
                                break;
                            }
                        }
                    }
                }

                if (rand == 3 && b < column - 1 && isPortal[a, b + 1] == false && isMonster[a, b + 1] == false) { //우
                    if (player[0] == a && player[1] == b + 1) {
                        life--;
                        lifeLabel.Text = "Life : " + life.ToString();
                    } else {
                        labels[a, b].Text = "□";
                        labels[a, b].Font = new Font("맑은고딕", 17);
                        isMonster[a, b] = false;
                        labels[a, b + 1].Text = "∑";
                        labels[a, b + 1].Font = new Font("맑은고딕", 14);
                        isMonster[a, b + 1] = true;
                        monster[i].setLocation(a, b + 1);
                    }
                    continue;
                } else if (rand == 3) {
                    if (b == column - 1 || isPortal[a, b + 1] == true || isMonster[a, b + 1] == true) {
                        for (int j = 0; j < 8; j++) {
                            if (cantMove[i, j] == 0) {
                                cantMove[i, j] = 3;
                                break;
                            }
                        }
                    }
                }

                if (rand == 4 && a < row - 1 && b < column - 1 && isPortal[a + 1, b + 1] == false && isMonster[a + 1, b + 1] == false) { //우하
                    if (player[0] == a + 1 && player[1] == b + 1) {
                        life--;
                        lifeLabel.Text = "Life : " + life.ToString();
                    } else {
                        labels[a, b].Text = "□";
                        labels[a, b].Font = new Font("맑은고딕", 17);
                        isMonster[a, b] = false;
                        labels[a + 1, b + 1].Text = "∑";
                        labels[a + 1, b + 1].Font = new Font("맑은고딕", 14);
                        isMonster[a + 1, b + 1] = true;
                        monster[i].setLocation(a + 1, b + 1);
                    }
                    continue;
                } else if (rand == 4) {
                    if (a == row - 1 || b == column - 1 || isPortal[a + 1, b + 1] == true || isMonster[a + 1, b + 1] == true) {
                        for (int j = 0; j < 8; j++) {
                            if (cantMove[i, j] == 0) {
                                cantMove[i, j] = 4;
                                break;
                            }
                        }
                    }
                }

                if (rand == 5 && a < row - 1 && isPortal[a + 1, b] == false && isMonster[a + 1, b] == false) { //하
                    if (player[0] == a + 1 && player[1] == b) {
                        life--;
                        lifeLabel.Text = "Life : " + life.ToString();
                    } else {
                        labels[a, b].Text = "□";
                        labels[a, b].Font = new Font("맑은고딕", 17);
                        isMonster[a, b] = false;
                        labels[a + 1, b].Text = "∑";
                        labels[a + 1, b].Font = new Font("맑은고딕", 14);
                        isMonster[a + 1, b] = true;
                        monster[i].setLocation(a + 1, b);
                    }
                    continue;
                } else if (rand == 5) {
                    if (a == row - 1 || isPortal[a + 1, b] == true || isMonster[a + 1, b] == true) {
                        for (int j = 0; j < 8; j++) {
                            if (cantMove[i, j] == 0) {
                                cantMove[i, j] = 5;
                                break;
                            }
                        }
                    }
                }

                if (rand == 6 && a < row - 1 && b > 0 && isPortal[a + 1, b - 1] == false && isMonster[a + 1, b - 1] == false) { //좌하
                    if (player[0] == a + 1 && player[1] == b - 1) {
                        life--;
                        lifeLabel.Text = "Life : " + life.ToString();
                    } else {
                        labels[a, b].Text = "□";
                        labels[a, b].Font = new Font("맑은고딕", 17);
                        isMonster[a, b] = false;
                        labels[a + 1, b - 1].Text = "∑";
                        labels[a + 1, b - 1].Font = new Font("맑은고딕", 14);
                        isMonster[a + 1, b - 1] = true;
                        monster[i].setLocation(a + 1, b - 1);
                    }
                    continue;
                } else if (rand == 6) {
                    if (a == row - 1 || b == 0 || isPortal[a + 1, b - 1] == true || isMonster[a + 1, b - 1] == true) {
                        for (int j = 0; j < 8; j++) {
                            if (cantMove[i, j] == 0) {
                                cantMove[i, j] = 6;
                                break;
                            }
                        }
                    }
                }

                if (rand == 7 && b > 0 && isPortal[a, b - 1] == false && isMonster[a, b - 1] == false) { //좌
                    if (player[0] == a && player[1] == b - 1) {
                        life--;
                        lifeLabel.Text = "Life : " + life.ToString();
                    } else {
                        labels[a, b].Text = "□";
                        labels[a, b].Font = new Font("맑은고딕", 17);
                        isMonster[a, b] = false;
                        labels[a, b - 1].Text = "∑";
                        labels[a, b - 1].Font = new Font("맑은고딕", 14);
                        isMonster[a, b - 1] = true;
                        monster[i].setLocation(a, b - 1);
                    }
                    continue;
                } else if (rand == 7) {
                    if (b == 0 || isPortal[a, b - 1] == true || isMonster[a, b - 1] == true) {
                        for (int j = 0; j < 8; j++) {
                            if (cantMove[i, j] == 0) {
                                cantMove[i, j] = 7;
                                break;
                            }
                        }
                    }
                }

                if (rand == 8 && a > 0 && b > 0 && isPortal[a - 1, b - 1] == false && isMonster[a - 1, b - 1] == false) { //좌상
                    if (player[0] == a - 1 && player[1] == b - 1) {
                        life--;
                        lifeLabel.Text = "Life : " + life.ToString();
                    } else {
                        labels[a, b].Text = "□";
                        labels[a, b].Font = new Font("맑은고딕", 17);
                        isMonster[a, b] = false;
                        labels[a - 1, b - 1].Text = "∑";
                        labels[a - 1, b - 1].Font = new Font("맑은고딕", 14);
                        isMonster[a - 1, b - 1] = true;
                        monster[i].setLocation(a - 1, b - 1);
                    }
                    continue;
                } else if (rand == 8) {
                    if (a == 0 || b == 0 || isPortal[a - 1, b - 1] == true || isMonster[a - 1, b - 1] == true) {
                        for (int j = 0; j < 8; j++) {
                            if (cantMove[i, j] == 0) {
                                cantMove[i, j] = 8;
                                break;
                            }
                        }
                    }
                }

                i--;
            }
        }

        public void CreateForm2(string str) {
            Form2 form2 = new Form2(str);
            form2.ShowDialog();
        }
    }
}
