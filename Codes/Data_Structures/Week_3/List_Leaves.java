/*
# List Leaves
Given a tree, you are supposed to list all the leaves in the order of top down, and left to right.
## Specification:
IN
Each input file contains one test case. For each case, the first line gives a positive integer N 
(≤10) which is the total number of nodes in the tree -- and hence the nodes are numbered from 0 to 
N?1. Then N lines follow, each corresponds to a node, and gives the indices of the left and right 
children of the node. If the child does not exist, a "-" will be put at the position. Any pair of 
children are separated by a space.
OUT
For each test case, print in one line all the leaves' indices in the order of top down, and left 
to right. There must be exactly one space between any adjacent numbers, and no extra space at the 
end of the line.
## Sample
IN
8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6
 
OUT
4 1 5

*/

//package Number;

import java.util.Scanner;
import java.util.Queue;
import java.util.LinkedList;

class Node {
	public int index;
	public int Left;
	public int Right;
}

class Tree{
	private Queue<Node> queue = new LinkedList<Node>();
	private Node[] tree;
	private int root;
	private int N;
	
	Tree(){
		Scanner in = new Scanner(System.in);
		this.N = in.nextInt();
		in.nextLine();
		int i = 0;
		String line;
		int[] check;
		if (this.N!=0) {
			this.tree = new Node[this.N];
			check = new int[this.N];
			for(;i<this.N;i++) {
				this.tree[i] = new Node();
				this.tree[i].index = i;
				line = in.nextLine();
//				System.out.println(line);
				String[] s = line.split(" ");
//				for(int j = 0;j<check.length;j++) {
//					check[j] = 0;
//				};
				if(!s[0].equals("-")) {
					this.tree[i].Left = Integer.parseInt(s[0]);
					check[this.tree[i].Left] = 1;
				}
				else {
					this.tree[i].Left = -1;
				}
				if(!s[1].equals("-")) {
					this.tree[i].Right = Integer.parseInt(s[1]);
					check[this.tree[i].Right] = 1;
				}
				else {
					this.tree[i].Right = -1;
				}
			}
			int j;
			for(j = 0;check[j]==1;j++);
			this.root = j;
			System.out.println(check);
		}
		else {
			this.root = -1;
		}
		in.close();
	}
	
	public void LevelOrderTraversal() {
		int flag = 0;
		Node n;
		if(this.N!=0) {
			this.queue.add(this.tree[this.root]);
			while(!this.queue.isEmpty()) {
				n = this.queue.remove();
//				System.out.println(n.index);
				if(n.Left!=-1) {
					this.queue.add(this.tree[n.Left]);
				}
				if(n.Right!=-1) {
					this.queue.add(this.tree[n.Right]);
				}
				if((n.Right==-1)&&(n.Left==-1)) {
					if(flag == 1) {
						System.out.print(" ");
					}
					flag = 1;
					System.out.print(n.index);
				}
			}
		}
	}
}

public class Main {
	public static void main(String[] args) {
		Tree t = new Tree();
		t.LevelOrderTraversal();

	}

}
