using System;

namespace PCRoomPackage {
    abstract class Game { //추상클래스 Game
        abstract public void Action();
    }
    //추상클래스 Game을 상속해서 override한 하위 클래스들
    class MexonGame : Game {
        public override void Action() {
            Console.WriteLine("This is MexonGame");
        }
    }
    class MDGame : Game {
        public override void Action() {
            Console.WriteLine("This is MDGame");
        }
    }
    class MetboardGame : Game {
        public override void Action() {
            Console.WriteLine("This is MetboardGame");
        }
    }

    class Computer {
        private int seatNum; //컴퓨터의 좌석번호
        private Game game;   //컴퓨터에 깔린 게임
        public void GameAction() {
            game.Action();
        }
        public int SeatNum {
            get { return seatNum; }
            set { seatNum = value; }
        }
         public Game GameInsatll {
            set { game = value; }
        }
    }

    class PCRoom {
        private Computer[,] arr = new Computer[5, 5]; //컴퓨터 이차원 배열로 선언
        public PCRoom() { //생성자
            int computernum = 1; //컴퓨터 번호
            int maxColumn = 1; //삼각형 모양 만들기 위한 변수

            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    Computer tempCom = new Computer();
                    tempCom.SeatNum = computernum; //임시 컴퓨터 tempCom에 컴퓨터 번호 설정

                    //좌석번호를 3으로 나눈 나머지에 따라 컴퓨터에 게임 할당(설치)
                    if (computernum % 3 == 1)
                        tempCom.GameInsatll = new MDGame();
                    else if (computernum % 3 == 2)
                        tempCom.GameInsatll = new MetboardGame();
                    else
                        tempCom.GameInsatll = new MexonGame();

                    arr[i, j] = tempCom; //이차원 배열에 번호와 게임이 설치된 컴퓨터 배치
                    ++computernum; //컴퓨터 번호 1 늘림

                    if (j + 1 == maxColumn) {
                        ++maxColumn;
                        break;
                    }
                }
            } //for문 종료
        } //생성자 종료

        public void PrintSeat() {
            Console.WriteLine("Numbers :");
            int maxColumn = 1;
            for(int i = 0; i < 5; ++i) {
                for(int j = 0; j < 5; ++j) {
                    int value = arr[i, j].SeatNum;
                    Console.Write(String.Format("{0,-8}", value));
                    if (j + 1 == maxColumn) {
                        Console.WriteLine();
                        ++maxColumn;
                        break;
                    }
                }
            }
        }

        public void TurnGameOn() {
            int maxColumn = 1;
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    Console.Write("Computer {0}'s Game : ", arr[i, j].SeatNum);
                    arr[i, j].GameAction();
                    if (j + 1 == maxColumn) {
                        ++maxColumn;
                        break;
                    }
                }
            }
        } //TurnGameOn 닫는 괄호
    } //PCRoom 클래스 닫는 괄호
} //namespace PCRoomPackage 닫는 괄호