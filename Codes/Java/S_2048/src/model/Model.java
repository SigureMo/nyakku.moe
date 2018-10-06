package model;

import java.util.ArrayList;

public class Model {
	private int[][] matrix = new int [4][4];
	
	public int max() {
		int m = 0;
		for(int[] line : matrix) {
			for(int unit : line) {
				if (unit > m){
					m = unit;
				}
			}
		}
		return m;
	}
	
	public void move(String command) {
		if (command.equals("a")){
			for (int i = 0 ; i < matrix.length ; i++) {
				int[] line = new int[matrix[i].length];
				for ( int j = 0,k = 0; j < matrix[i].length ; j++) {
					if(matrix[i][j] != 0) {
						line[k] = matrix[i][j];
						k++;
					}
				}
				matrix[i] = line;
				for ( int j = 0; j < matrix[i].length -1; j++) {
					if (matrix[i][j] == 0) {
						break;
					}
					else if (matrix[i][j] == matrix[i][j+1]) {
						matrix[i][j] += matrix[i][j+1];
						for (int k = 0; j+k+1 < matrix[i].length -1 ; k++) {
							matrix[i][j+k+1] = matrix[i][j+k+2];
						}
						matrix[i][matrix[i].length-1] = 0;
					}
					
				}
			}
		}
		else if (command.equals("d")) {
			left_right();
			move("a");
			left_right();
		}
		else if (command.equals("w")) {
			left_up();
			move("a");
			left_up();
		}
		else if (command.equals("s")) {
			left_down();
			move("a");
			left_down();
		}
	}
	
	public void left_up() {
		int[][] new_matrix = new int[matrix[0].length][matrix.length];
		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0; j < matrix[i].length; j++) {
				new_matrix[j][i] = matrix[i][j];
			}
		}
		matrix = new_matrix;
	}
	
	public void left_down() {
		int[][] new_matrix = new int[matrix[0].length][matrix.length];
		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0; j < matrix[i].length; j++) {
				new_matrix[matrix[i].length-j-1][matrix.length-i-1] = matrix[i][j];
			}
		}
		matrix = new_matrix;
	}
	
	public void left_right() {
		int[][] new_matrix = new int[matrix.length][matrix[0].length];
		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0; j < matrix[i].length; j++) {
				new_matrix[i][matrix[i].length-j-1] = matrix[i][j];
			}
		}
		matrix = new_matrix;
	}
	
	public void newgame() {
		int point_x1 = (int)(Math.random() * matrix.length);
		int point_x2 = (int)(Math.random() * matrix.length);
		int point_y1 = (int)(Math.random() * matrix[0].length);
		int point_y2 = (int)(Math.random() * matrix[0].length);
		while((point_x1 == point_x2)&&(point_y1 == point_y2)) {
			point_x2 = (int)(Math.random() * 4);
			point_y2 = (int)(Math.random() * 4);
		}
		matrix[point_x1][point_y1] = 2 ;
		matrix[point_x2][point_y2] = 2 ;
	}
	
	public void increase() {
		ArrayList<int[]> empty = new ArrayList<int[]>();
		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0;j < matrix[i].length;j++) {
				if (matrix[i][j] == 0 ) {
					int[] a = new int[2];
					a[0] = i;
					a[1] = j;
					empty.add(a);
				}
			}
		}
		int index = (int)(Math.random() * empty.size());
		int x = empty.get(index)[0];
		int y = empty.get(index)[1];
		int m = (int)(Math.random() * max());
		int value = 2;
		for (int i = 0; i < m ; i++) {
			if (i == 4 || i == 8 || i ==16 ||
					i == 32 || i == 64 || i == 128 ||
					i == 256 || i == 512 || i == 1024 ||
					i == 2048 || i == 4096 || i == 8192){
				value = i;
			}
		}
		matrix[x][y] = value ;
	}
		
	public String toString() {
		StringBuffer sb = new StringBuffer();
		for (int[] line : matrix) {
			for (int unit : line) {
				sb.append(unit+" ");
			}
			sb.append("\n");
		}
		return sb.toString();
	}
		

	
    public static void main(String[] args) {
    	Model model = new Model();
    	model.newgame();
    	System.out.println(model);
    	model.move("left");
    	System.out.println(model);
    	model.increase();
    	System.out.println(model);
    	model.move("right");
    	System.out.println(model);
    	model.increase();
    	System.out.println(model);
    	model.move("up");
    	System.out.println(model);
    	model.increase();
    	System.out.println(model);
    	model.move("down");
    	System.out.println(model);
    	model.increase();
    	System.out.println(model);
}
}
