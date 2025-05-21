import java.util.Arrays;

class RotateArray {
    public static void rotate(int[] nums, int k) {
        int n = nums.length;
        k = k % n;

        rotateSection(nums, 0, n - 1);
        rotateSection(nums, 0, k - 1);
        rotateSection(nums, k, n - 1);
    }

    private static void rotateSection(int[] nums, int leftIndex, int rightIndex) {
        while (leftIndex < rightIndex) {
            int temp = nums[leftIndex];
            nums[leftIndex] = nums[rightIndex];
            nums[rightIndex] = temp;
            leftIndex++;
            rightIndex--;
        }
    }

    public static class Main

    {

        public static void main (String[]args){
        int[] nums = {1, 2, 3, 4, 5, 6, 7, 8};
        int k = 3;
        rotate(nums, k);
        System.out.println("Rotated array: " + Arrays.toString(nums));
    }
    }
}
