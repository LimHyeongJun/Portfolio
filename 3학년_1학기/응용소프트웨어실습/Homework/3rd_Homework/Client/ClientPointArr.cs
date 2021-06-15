using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Client {
    class ClientPointArr {
        private List<Point> list;

        public ClientPointArr() {
            list = new List<Point>();
        }

        public void setPoint(List<Point> list) {
            this.list = list;
        }

        public List<Point> getList() {
            return list;
        }

        public void Add(Point point) {
            this.list.Add(point);
        }

        public void sort() {
            this.list.Distinct().ToList();
        }

        public void Clear() {
            this.list.Clear();
        }
    }
}
