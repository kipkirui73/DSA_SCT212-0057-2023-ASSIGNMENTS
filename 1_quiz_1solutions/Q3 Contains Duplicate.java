import java.util.Arrays;
class duplicate {


    public boolean duplicate(int[] nums) {
        Arrays.sort(nums);
        for (int i = 0; i < nums.length - 1; i++) {
            if (nums[i] == nums[i + 1]) {
                return true;
            }
        }
        return false;
    }

    public static class Main {
        public static void main(String[] args) {
            int[] nums = {1, 2, 3, 4, 5, 6, 2};


            duplicate obj = new duplicate();
            boolean result = obj.duplicate(nums);

            System.out.println("Contains duplicate: " + result);
        }
    }
}