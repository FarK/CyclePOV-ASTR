package main;

import java.io.BufferedReader;
import java.io.FileReader;

public class POVImage
{
	public static int NUM_SPOKES 	= 128;
	public static int NUM_LEDS 		= 28;
	public static int NUM_COLORS 	= 3;
	
	public static int[][][] image = new int[NUM_SPOKES][NUM_LEDS][NUM_COLORS];
	
	static
	{
		try
		{
			FileReader fileReader = new FileReader("awesome2.txt");
			BufferedReader bufferedReader = new BufferedReader(fileReader);
	        
	        String line = bufferedReader.readLine();
	        String[] numbers = line.split(" ");
	        
	        int index = 0;
	        for(int spoke = 0; spoke < NUM_SPOKES; spoke++)
	    	for(int led = 0; led < NUM_LEDS; led++)
			for(int color = 0; color < NUM_COLORS; color++)
			{
				image[spoke][led][color] = Integer.parseInt(numbers[index++]);
			}
	        
	        bufferedReader.close();
	        fileReader.close();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}
