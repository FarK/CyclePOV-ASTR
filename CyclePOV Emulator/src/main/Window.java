package main;

import java.awt.Color;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class Window extends Frame implements Runnable
{
	private static final long serialVersionUID = 870212695309881522L;
	
	private static final int WIDTH = 600;
	private static final int HEIGHT = 600;
	private static final int LEFTBORDER = 3;
	private static final int UPBORDER = 25;
	
	private static final int RADIUS = (int)(WIDTH * 0.450);
	private static final int LED_RADIUS = 10;
		
	private Image offImg = null;
	private Graphics offGraphics;
	
	private int max_spokes = 0;
	
	public Window(String name)
	{
		super(name);
	
		//Controles de la ventana.
		this.addWindowListener(new WindowHandler());
		this.addKeyListener(new KeyboardController());
		
		setSize(WIDTH + 2 * LEFTBORDER, HEIGHT + UPBORDER + LEFTBORDER);
		setLocation((Toolkit.getDefaultToolkit().getScreenSize().width / 2) - (getWidth() / 2), (Toolkit.getDefaultToolkit().getScreenSize().height / 2) - (getHeight() / 2));
		setResizable(false);
		
		Thread t = new Thread(this);
		t.start();
		
		setVisible(true);
	}
	
	//Metodos para dibujar la pantalla.
	public void update(Graphics g)
	{
		paint(g);
	}
	public void paint(Graphics g)
	{
		if (offImg == null)
		{
			offImg = createImage(WIDTH, HEIGHT);
			offGraphics = offImg.getGraphics();
		}
		
		offGraphics.setColor(Color.WHITE);
		offGraphics.fillRect(0, 0, offImg.getWidth(null) - 1, offImg.getHeight(null) - 1);
		
		offGraphics.setColor(Color.RED);
		offGraphics.drawRect(0, 0, offImg.getWidth(null) - 1, offImg.getHeight(null) - 1);
		
		offGraphics.setColor(Color.BLACK);
		
		// Paint the wheel
		Point center = new Point(WIDTH / 2, HEIGHT / 2);
		Point pixel_position = new Point();
		Point direction_vector;
		
		int led_to_sample = 0;
		for(int spoke = 0; spoke < max_spokes; spoke++)
		{
			double angle = spoke * 2 * Math.PI / POVImage.NUM_SPOKES;
			
			for(int led = 0; led < POVImage.NUM_LEDS / 2; led++)
			{
				direction_vector = new Point((int)(RADIUS * Math.cos(angle)), -(int)(RADIUS * Math.sin(angle)));
				
				pixel_position.x = center.x + (direction_vector.x * (2 * led + 2)) / (POVImage.NUM_LEDS);
				pixel_position.y = center.y + (direction_vector.y * (2 * led + 2)) / (POVImage.NUM_LEDS);
				
				led_to_sample = led;
				offGraphics.setColor(new Color(POVImage.image[spoke][led_to_sample][1], POVImage.image[spoke][led_to_sample][0], POVImage.image[spoke][led_to_sample][2]));
				offGraphics.fillOval(pixel_position.x - LED_RADIUS / 2, pixel_position.y - LED_RADIUS / 2, LED_RADIUS, LED_RADIUS);
				
				direction_vector = new Point((int)(RADIUS * Math.cos(angle - Math.PI / 2)), -(int)(RADIUS * Math.sin(angle - Math.PI / 2)));
				
				pixel_position.x = center.x + (direction_vector.x * (2 * led + 3)) / (POVImage.NUM_LEDS);
				pixel_position.y = center.y + (direction_vector.y * (2 * led + 3)) / (POVImage.NUM_LEDS);
				
				led_to_sample = led + POVImage.NUM_LEDS / 2;
				offGraphics.setColor(new Color(POVImage.image[spoke][led_to_sample][1], POVImage.image[spoke][led_to_sample][0], POVImage.image[spoke][led_to_sample][2]));
				offGraphics.fillOval(pixel_position.x - LED_RADIUS / 2, pixel_position.y - LED_RADIUS / 2, LED_RADIUS, LED_RADIUS);
			}
		}
		
		g.drawImage(offImg, LEFTBORDER, UPBORDER, this);
	}
	
	@Override
	public void run()
	{
		while(true)
		{			
			repaint();
			
			if(max_spokes < POVImage.NUM_SPOKES)
			{
				max_spokes++;
			}
			
			try{synchronized(this){wait(50);}}
			catch(InterruptedException e){}
		}
	}
	
	//---- CLASES ----//
	//Clase que se encarga de los botones de la barra de la ventana y demas cosas.
	private class WindowHandler extends WindowAdapter
	{
		public void windowClosing(WindowEvent we)
		{
			System.exit(0);
		}
		public void windowIconified(WindowEvent e)
		{
			setVisible(false);
		}
	}
	
	//Clase que controla los eventos que genera el teclado.
	private class KeyboardController implements KeyListener
	{
		public void keyPressed(KeyEvent ev)
		{
			if(ev.getKeyCode() == KeyEvent.VK_ENTER)
			{
				max_spokes = 0;
			}
		}
		public void keyTyped(KeyEvent ev){}
		public void keyReleased(KeyEvent ev){}
	}	
}