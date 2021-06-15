namespace RogueLikeGame {
    class Monster {
        public int[] location = new int[2];

        public Monster() {
            location[0] = 0;
            location[1] = 0;
        }

        public void setLocation(int a, int b) {
            location[0] = a;
            location[1] = b;
        }

        public int[] getLocation() {
            return location;
        }
    }
}
