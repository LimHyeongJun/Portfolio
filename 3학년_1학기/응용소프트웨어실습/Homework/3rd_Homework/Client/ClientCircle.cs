using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Client {
    class ClientCircle {
        private Rectangle rectC;
        private int thick;
        private bool isSolid;
        private bool isBrush;
        private Color lineColor;
        private SolidBrush brush;

        public ClientCircle() {
            rectC = new Rectangle();
            thick = 1;
            isSolid = true;
            isBrush = false;
            lineColor = Color.Black;
            brush = new SolidBrush(Color.White);
        }

        public void setRectC(Point start, Point finish, int thick, bool isSolid, bool isBrush, Color lineColor, Color insideColor) {
            rectC.X = Math.Min(start.X, finish.X);
            rectC.Y = Math.Min(start.Y, finish.Y);
            rectC.Width = Math.Abs(start.X - finish.X);
            rectC.Height = Math.Abs(start.Y - finish.Y);
            this.thick = thick;
            this.isSolid = isSolid;
            this.isBrush = isBrush;
            this.lineColor = lineColor;
            this.brush = new SolidBrush(insideColor);
        }

        public Rectangle getRectC() {
            return rectC;
        }

        public int getThick() {
            return thick;
        }

        public bool getSolid() {
            return isSolid;
        }

        public Color getLineColor() {
            return lineColor;
        }

        public SolidBrush getBrush() {
            return brush;
        }

        public bool brushDecide() {
            return isBrush;
        }
    }
}
