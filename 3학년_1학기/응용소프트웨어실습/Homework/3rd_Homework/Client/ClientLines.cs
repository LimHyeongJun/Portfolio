using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Client {
    class ClientLines {
        private Point[] point = new Point[2];
        private int thick;
        private bool isSolid;
        private Color color;

        public ClientLines() {
            point[0] = new Point();
            point[1] = new Point();
            thick = 1;
            isSolid = true;
            color = Color.Black;
        }

        public void setPoint(Point start, Point finish, int thick, bool isSolid, Color color) {
            point[0] = start;
            point[1] = finish;
            this.thick = thick;
            this.isSolid = isSolid;
            this.color = color;
        }

        public Point getPoint1() {
            return point[0];
        }

        public Point getPoint2() {
            return point[1];
        }

        public int getThick() {
            return thick;
        }

        public bool getSolid() {
            return isSolid;
        }

        public Color getColor() {
            return color;
        }
    }
}
