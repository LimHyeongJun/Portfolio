using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Client {
    class ClientPencil {
        private List<Point> list;
        private int thick;
        private bool isSolid;
        private Color lineColor;

        public ClientPencil() {
            list = new List<Point>();
            thick = 1;
            isSolid = true;
            lineColor = Color.Black;
        }

        public void setPoint(List<Point> list, int thick, bool isSolid, Color color) {
            this.list = list;
            this.thick = thick;
            this.isSolid = isSolid;
            this.lineColor = color;
        }

        public List<Point> getList() {
            return list;
        }

        public int getThick() {
            return thick;
        }

        public bool getSolid() {
            return isSolid;
        }

        public Color getColor() {
            return lineColor;
        }
    }
}
