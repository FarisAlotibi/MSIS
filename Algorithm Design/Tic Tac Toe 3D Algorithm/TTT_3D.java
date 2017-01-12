/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package project_5;
/**
 *
 * @author FRISCA
 */

import java.util.*;

public class TTT3D 
{
	public static void main(String[] args)
	{
		Grid threeDboard = new Grid();
		threeDboard.startTheGame();
	}
}   

class Grid {
    public int SIZE = 4, didWin = 0, reqLength = 4;
    public int[][][] threeDboard = new int[SIZE][SIZE][SIZE];
    public int[] lastPMove = new int[SIZE]; // elemenite
    public static enum GameStatus { ILLEGAL, ONGOING, TIE, USER_WON, COMPUTER_WON; }

    public void startTheGame()
    {
    	System.out.println("Welcome to Play 3D Tic Tac Toe Game!\n");
        Scanner io = new Scanner(System.in);
 
        System.out.println("You need to choose who's going to play the game first? "
                         + "(X: you the 1st player, O: AI opponent the 1st player)");

        String c_Player = "";
        while(!"X".equals(c_Player) && !"O".equals(c_Player))
        {
        	c_Player = io.next();
        }

        System.out.println("The 3D Board Initialization process...\n");
        printthreeDboard();
        GameStatus gmStatus = GameStatus.ONGOING;
        
        while (gmStatus == GameStatus.ONGOING) 
        {
        	if("X".equals(c_Player))
        	{
	            int x, y, z;
	            System.out.print("Enter the level: ");
	            x = io.nextInt();
	            System.out.print("Enter the row: ");
	            y = io.nextInt();
	            System.out.print("Enter the column: ");
	            z = io.nextInt();
	            
            	gmStatus = setPiece(x, y, z, 1);
            	

            	if (gmStatus == GameStatus.ONGOING) 
            	{
            		printthreeDboard();
            		c_Player = "O";
            	}
            	else if (gmStatus == GameStatus.USER_WON)
            	{
            		printthreeDboard();
            	}
            	else if(gmStatus == GameStatus.ILLEGAL) 
            	{
	            	System.out.println("\n********** ERROR: Wrong Choice already the Spot is selected! **********");
	            	gmStatus = GameStatus.ONGOING;
	            }
			}
			if("O".equals(c_Player)) {
            	gmStatus = makingTheMove();
            	printthreeDboard();
            	c_Player = "X";
			}
        }

        if (gmStatus == GameStatus.USER_WON)
        	System.out.println("\nYOU are the WINNER!");
        else if (gmStatus == GameStatus.COMPUTER_WON)
        	System.out.println("\nAI Opponent is the WINNER!");
        
    }

    public GameStatus makingTheMove()
	{
		GameStatus gmStatus = GameStatus.ILLEGAL;
        while (gmStatus == GameStatus.ILLEGAL)
        {
            int x = randInt(0, SIZE - 1), y = randInt(0, SIZE - 1), z = randInt(0, SIZE - 1);
            
            gmStatus = setPiece(x,y,z, 2);
            if (gmStatus == GameStatus.ONGOING || gmStatus == GameStatus.COMPUTER_WON)
            {
                System.out.printf("AI Opponent played on this level %d: (%d,%d)%n", x, y, z);
            }
        }
        return gmStatus;
    }
    
        public GameStatus setPiece(int x, int y, int z, int player)
    {
    	GameStatus gmStatus = GameStatus.ILLEGAL;

        if (threeDboard[x][y][z] == 0)
        {
            threeDboard[x][y][z] = player;
            lastPMove[0] = x; lastPMove[1] = y; lastPMove[2] = z; lastPMove[3] = player;
            if (checkTheWinning()) 
            {
            	if(player == 1)
            		gmStatus = GameStatus.USER_WON;
            	
            	else
            		gmStatus = GameStatus.COMPUTER_WON;
            }
            else 
            	gmStatus = GameStatus.ONGOING;
        }

        return gmStatus;
    }
    
    public int randInt(int min, int max) {
        Random rand = new Random();

        int randomNum = rand.nextInt((max - min) + 1) + min;

        return randomNum;
    }

	public boolean checkTheLayer(int x)
	{
		//Check by rows
		for(int i = 0; i < SIZE; i++){
			if(threeDboard[x][i][0] == threeDboard[x][i][1] && threeDboard[x][i][0] == threeDboard[x][i][2] && threeDboard[x][i][0] == threeDboard[x][i][3] && threeDboard[x][i][0] != 0) 
				return true;
		}
		
		//CHeck Columns
		for(int j = 0; j < SIZE; j++){
			if(threeDboard[x][0][j] == threeDboard[x][1][j] && threeDboard[x][0][j] == threeDboard[x][2][j] && threeDboard[x][0][j] == threeDboard[x][3][j] && threeDboard[x][0][j] != 0) 
				return true;
		}
		
		//Top left to bottom right diagonal
		if(threeDboard[x][0][0] == threeDboard[x][1][1] && threeDboard[x][0][0] == threeDboard[x][2][2] && threeDboard[x][0][0] == threeDboard[x][3][3] && threeDboard[x][0][0] != 0) 
			return true;
		
		
		//Bottom left to top right
		if(threeDboard[x][3][0] == threeDboard[x][2][1] && threeDboard[x][3][0] == threeDboard[x][1][2] && threeDboard[x][3][0] == threeDboard[x][0][3] && threeDboard[x][3][0] != 0) 
			return true;
		
		
		return false;
	}

	private boolean checkTheWinning()
	{
		/* winning positions: 40 */
		//Scenario 1 "Statndard"
		if(checkTheLayer(0) || checkTheLayer(1) || checkTheLayer(2) || checkTheLayer(3)) 
			return true;
		
		/* winning positions: 16 */
		//Scenario 2 "straight up / down"
		int i, j;
		for(i = 0; i < SIZE; i++){
			for(j = 0; j < SIZE; j++){
				if(threeDboard[0][i][j] == threeDboard[1][i][j] && threeDboard[0][i][j] == threeDboard[2][i][j] && threeDboard[0][i][j] == threeDboard[3][i][j]
					&& threeDboard[0][i][j] != 0)
					return true;
			}
		}
		
		/* winning positions: 4 */
		//Scenario 3 "Straight Staircases"
		//First by row
		for(i = 0; i < SIZE; i++){
			if(threeDboard[0][i][0] == threeDboard[1][i][1] && threeDboard[0][i][0] == threeDboard[2][i][2] && threeDboard[0][i][0] == threeDboard[3][i][3]
				&& threeDboard[0][i][0] != 0)
				return true;
		}
		/* winning positions: 4 */
		for(i = 0; i < SIZE; i++){
			if(threeDboard[0][i][3] == threeDboard[1][i][2] && threeDboard[0][i][3] == threeDboard[2][i][1] && threeDboard[0][i][3] == threeDboard[3][i][0]
				&& threeDboard[0][i][3] != 0)
				return true;
		}
		
		/* winning positions: 4 */
		//Now by column
		for(j = 0; j < SIZE; j++){
			if(threeDboard[0][0][j] == threeDboard[1][1][j] && threeDboard[0][0][j] == threeDboard[2][2][j] && threeDboard[0][0][j] == threeDboard[3][3][j]
				&& threeDboard[0][0][j] != 0)
				return true;
		}
		/* winning positions: 4 */
		for(j = 0; j < SIZE; j++){
			if(threeDboard[0][3][j] == threeDboard[1][2][j] && threeDboard[0][3][j] == threeDboard[2][1][j] && threeDboard[0][3][j] == threeDboard[3][0][j]
				&& threeDboard[0][3][j] != 0)
				return true;
		}
		
		/* winning positions: 4 */
		//Scenario 4 "The Diagonal Staircase"
		//Top left to bottom right
		if(threeDboard[0][0][0] == threeDboard[1][1][1] && threeDboard[0][0][0] == threeDboard[2][2][2] && threeDboard[0][0][0] == threeDboard[3][3][3]
			&& threeDboard[0][0][0] != 0)
			return true;
		

		if(threeDboard[0][3][3] == threeDboard[1][2][2] && threeDboard[0][3][3] == threeDboard[2][1][1] && threeDboard[0][3][3] == threeDboard[3][0][0]
			&& threeDboard[0][3][3] != 0)
			return true;
		

		//Bottom Left to Top Right
		if(threeDboard[0][3][0] == threeDboard[1][2][1] && threeDboard[0][3][0] == threeDboard[2][1][2] && threeDboard[0][3][0] == threeDboard[3][0][3]
			&& threeDboard[0][3][0] != 0)
			return true;
		

		if(threeDboard[0][0][3] == threeDboard[1][1][2] && threeDboard[0][0][3] == threeDboard[2][2][1] && threeDboard[0][0][3] == threeDboard[3][3][0]
			&& threeDboard[0][0][3] != 0)
			return true;
		
		
		//No Win
		return false;
	}



//    public void printthreeDboard()
//    {
//    	System.out.println();
//        for(int y = 0; y < 4; y++) // row
//        {
//            if(y == 0) System.out.print("  ");
//            for(int z = 0; z < 4; z++) // level
//            {
//                for(int x = 0; x < 4; x++) // column
//                {
//                    if(threeDboard[z][y][x] == 1)
//                        System.out.printf(" X ");
//                    else if(threeDboard[z][y][x] == 2)
//                        System.out.printf(" O ");
//                    else
//                        System.out.printf(" . ");
//                }
//                System.out.print("  ");
//            }
//
//            if(y == 0) 
//               System.out.print("\n\n^ ");
//            else if(y == 1) 
//               System.out.print("\n| \ny ");
//            else
//               System.out.print("\n\n  ");
//
//        }
//        System.out.println("  z -->");
//        System.out.println("      x = 0         x = 1         x = 2         x = 3\n");	
//    }
        //*********************************************************************
    public void printthreeDboard()
    {
    	System.out.println();
        for(int i = 0; i < 4; i++)
        {
            System.out.print("         ________________" );

            System.out.print(" <- LEVEL: " + i + "\n");

            for(int j = 0; j < 4; j++)
            {
                // out.print(j + " ");
                if(i == 0)
                {
                    if(j == 0) System.out.print(j + " ----> ");
                    else if(j == 1) System.out.print(j + " --> ");
                    else if(j == 2) System.out.print(j + " ->");
                    else System.out.print(j+ " ");
                }
                else
                {
                    if(j == 0) System.out.print("       ");
                    else if(j == 1) System.out.print("     ");
                    else if(j == 2) System.out.print("   ");
                    else System.out.print(" ");
                }

                for(int k = 0; k < 4; k++)
                {
                    if(threeDboard[i][j][k] == 1)
                            System.out.print(" X   ");
                    else if(threeDboard[i][j][k] == 2)
                            System.out.print(" O   ");
                    else
                            System.out.print(" .   ");
                }

                if(i != 3)
                {
                    if(j == 0) System.out.print("");
                    else if(j == 1) System.out.print("   ");
                    else if(j == 2) System.out.print("     ");
                    else System.out.print("       ");
                }
                System.out.println();

                if(j == 0) System.out.print("      ");
                else if(j == 1) System.out.print("    ");
                else if(j == 2) System.out.print( "  ");
                else System.out.print("");


                if(i != 3)
                {
                    if(j == 0) System.out.print("  ");
                    else if(j == 1) System.out.print("    ");
                    else if(j == 2) System.out.print("      ");
                    else System.out.print("        ");
                }
                System.out.println();
            }
        }
    }
}