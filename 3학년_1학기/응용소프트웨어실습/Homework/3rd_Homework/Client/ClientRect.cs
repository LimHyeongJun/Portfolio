using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Client {
    class ClientRect {
        private Rectangle rect;
        private int thick;
        private bool isSolid;
        private bool isBrush;
        private Color lineColor;
        private SolidBrush brush;

        public ClientRect() {
            rect = new Rectangle();
            thick = 1;
            isSolid = true;
            isBrush = false;
            lineColor = Color.Black;
            brush = new SolidBrush(Color.White);
        }

        public void setRect(Point start, Point finish, int thick, bool isSolid, bool isBrush, Color lineColor, Color insideColor) {
            rect.X = Math.Min(start.X, finish.X);
            rect.Y = Math.Min(start.Y, finish.Y);
            rect.Height = Math.Abs(finish.Y - start.Y);
            rect.Width = Math.Abs(finish.X - start.X);
            this.thick = thick;
            this.isSolid = isSolid;
            this.isBrush = isBrush;
            this.lineColor = lineColor;
            this.brush = new SolidBrush(insideColor);
        }

        public Rectangle getRect() {
            return rect;
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
