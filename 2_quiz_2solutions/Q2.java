class ListNode {
    int val;
    ListNode next;

    ListNode(int val) {
        this.val = val;
        this.next = null;
    }
}

class Solution2 {

    public ListNode detectCycle(ListNode head) {
        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) {
                slow = head;
                while (slow != fast) {
                    slow = slow.next;
                    fast = fast.next;
                }
                return slow;
            }
        }
        return null;
    }
    public static class Main {
        public static void main(String[] args) {

            ListNode head = new ListNode(3);
            ListNode second = new ListNode(2);
            ListNode third = new ListNode(0);
            ListNode fourth = new ListNode(-4);

            head.next = second;
            second.next = third;
            third.next = fourth;
            fourth.next = second;

            Solution2 s = new Solution2();
            ListNode cycleStart = s.detectCycle(head);
            if (cycleStart != null) {
                System.out.println("Cycle starts at node with value: " + cycleStart.val);
            } else {
                System.out.println("No cycle");
            }
        }
    }
}