namespace RogueLikeGame {
    class Stage {
        private int row; //가로
        private int column; //세로
        private Portal[] portal; //포탈
        private Monster[] monster; // 몬스터

        public void setRow(int row) {
            this.row = row;
        }

        public void setColumn(int column) {
            this.column = column;
        }

        public void setPortal(Portal[] portal) {
            this.portal = portal;
        }

        public void setMonster(Monster[] monster) {
            this.monster = monster;
        }

        public int getRow() {
            return row;
        }

        public int getColumn() {
            return column;
        }

        public Portal[] getPortal() {
            return portal;
        }

        public Monster[] getMonster() {
            return monster;
        }
    }
}
