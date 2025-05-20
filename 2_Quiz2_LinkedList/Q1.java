class ListNode {
    int val;
    ListNode next;
    ListNode(int val) {
        this.val = val;
        this.next = null;
    }
}

class Solution1 {

    public boolean hasCycle(ListNode head) {
        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;           
            fast = fast.next.next;     
            if (slow == fast) {
                return true;            
            }
        }
        return false;                  
    }

    public static void main(String[] args) {
        
        ListNode head = new ListNode(3);
        ListNode second = new ListNode(2);
        ListNode third = new ListNode(0);
        ListNode fourth = new ListNode(-4);

        
        head.next = second;
        second.next = third;
        third.next = fourth;

        
        fourth.next = second;

        Solution1 s = new Solution1();
        boolean result = s.hasCycle(head);
        System.out.println("Has cycle: " + result);  
    }
}

