using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PCRoomPackage;

namespace MainProgram {
    class Program {
        static void Main(string[] args) {
            PCRoom room = new PCRoom();

            room.PrintSeat();
            room.TurnGameOn();
        }
    }
}

//이 파일을 내용 수정 불가