namespace RogueLikeGame {
    class Portal {
        private int[] location = new int[2];
        private int connectStage;
                
        public Portal() {
            location[0] = 0;
            location[1] = 0;
            connectStage = 0;
        }

        public void setConnectStage(int a) {
            connectStage = a;
        }

        public void setLocation(int a, int b) {
            location[0] = a;
            location[1] = b;
        }

        public int[] getLocation() {
            return this.location;
        }

        public int getConnectStage() {
            return connectStage;
        }
    }
}
