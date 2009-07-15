package ui;

import game.DiceTray;
import game.Die;
import game.Lexicon;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.SwingUtilities;
import javax.swing.Timer;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class Window extends JFrame
{
	private static final long serialVersionUID = 1L;

	private JButton trigger;
	private JLabel status;
	private JTextArea input;
	private JLabel[][] grid;

	private boolean running;
	private int time;
	private Timer timer;
	private Lexicon lexicon;
	private DiceTray diceTray;
	private Thread search;
	private List<String> allWords;

	public Window()
	{
		this.allWords = new ArrayList<String>();
		
		this.setTitle(Messages.getString("Window.title"));
		this.setPreferredSize(new Dimension(300, 400));
		this.getContentPane().add(this.layoutUi());
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.installListeners();
		this.pack();
	}

	private void startGame()
	{
		this.running = true;
		
		this.diceTray = new DiceTray();
		Die[][] dice = this.diceTray.getDice();
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this.grid[i][j].setText(dice[i][j].toString());

		this.status.setText(MessageFormat.format(Messages.getString("Window.timeRemaining"), Messages.getString("Window.defaultTime"))); 
		this.trigger.setText(Messages.getString("Window.stop"));
		this.input.setEnabled(true);
		this.input.requestFocus();

		this.allWords.clear();
		this.search = this.backgroundSearch();
		this.search.start();
		this.time = 180;
		this.timer.start();
	}

	private void stopGame()
	{
		this.running = false;
		
		if (this.search.isAlive())
		{
			try
			{
				this.search.join();
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}

		this.timer.stop();
		this.showReport();

		for (JLabel[] row : this.grid)
			for (JLabel col : row)
				col.setText(Messages.getString("Window.defaultGamePiece"));

		this.status.setForeground(Color.BLACK);
		this.status.setText(Messages.getString("Window.defaultStatus"));
		this.trigger.setText(Messages.getString("Window.start"));
		this.input.setText("");
		this.input.setEnabled(false);
		this.trigger.requestFocus();
	}

	private void showReport()
	{
		JTextArea ta = new JTextArea(12, 40);
		ta.setText(new Score(this.allWords).score(this.input.getText().toLowerCase().trim()));
		ta.setCaretPosition(0);
		ta.setEditable(false);
		ta.setLineWrap(true);
		ta.setWrapStyleWord(true);
		JScrollPane sp = new JScrollPane(ta);
		JOptionPane.showMessageDialog(this, sp);
	}

	private Thread backgroundSearch()
	{
		return new Thread(new Runnable() {
			public void run()
			{
				long start = System.currentTimeMillis();

				if (Window.this.lexicon == null)
					Window.this.lexicon = new Lexicon();

				Window.this.lexicon.filter(Window.this.diceTray.toPattern());

				for (String s : Window.this.lexicon)
					if (Window.this.diceTray.stringFound(s))
						Window.this.allWords.add(s);

				long finish = System.currentTimeMillis();
				System.out.println("Total: " + (finish - start) + " ms");
			}
		});
	}

	private void installListeners()
	{
		this.timer = new Timer(1000, new ActionListener() {
			public void actionPerformed(ActionEvent e)
			{
				if (Window.this.time == 0)
				{
					Window.this.stopGame();
					return;
				}

				Window.this.time--;

				final String minutes = time / 60 + "";
				final int mod = time % 60;
				final String seconds = (mod < 10) ? ("0" + mod) : ("" + mod); 
				Window.this.status.setText(MessageFormat.format(
						Messages.getString("Window.timeRemaining"), MessageFormat.format(Messages.getString("Window.timeFormat"), minutes, seconds)));

				if (Window.this.time <= 60)
					Window.this.status.setForeground(Color.RED);
			}
		});

		this.trigger.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0)
			{
				if (Window.this.running)
					Window.this.stopGame();
				else
					Window.this.startGame();
			}
		});
	}

	private JPanel layoutUi()
	{
		JPanel panel = new JPanel(new BorderLayout());

		panel.add(this.layoutControlPanel(), BorderLayout.NORTH);
		panel.add(this.layoutGamePanel(), BorderLayout.CENTER);
		panel.add(this.layoutInputPanel(), BorderLayout.SOUTH);

		return panel;
	}

	private JPanel layoutControlPanel()
	{
		GridBagLayout g = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		JPanel panel = new JPanel(g);
		c.weightx = 1.0;
		c.weighty = 1.0;
		c.insets = new Insets(4, 4, 0, 4);

		this.trigger = new JButton(Messages.getString("Window.start"));
		this.status = new JLabel(Messages.getString("Window.defaultStatus"));

		c.anchor = GridBagConstraints.WEST;
		g.setConstraints(this.status, c);
		panel.add(this.status);

		c.anchor = GridBagConstraints.EAST;
		g.setConstraints(this.trigger, c);
		panel.add(this.trigger);

		return panel;
	}

	private JPanel layoutGamePanel()
	{
		JPanel panel = new JPanel(new GridLayout(4, 4));

		this.grid = new JLabel[4][4];

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				grid[i][j] = new JLabel(Messages.getString("Window.defaultGamePiece"));
				grid[i][j].setVerticalAlignment(JLabel.CENTER);
				grid[i][j].setHorizontalAlignment(JLabel.CENTER);
				grid[i][j].setFont(new Font(grid[i][j].getFont().getFontName(), Font.BOLD, 20));
				panel.add(grid[i][j]);
			}
		}

		return panel;
	}

	private JPanel layoutInputPanel()
	{
		GridBagLayout g = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		JPanel panel = new JPanel(g);

		this.input = new JTextArea(8, 0);
		this.input.setEnabled(false);

		JScrollPane scroll = new JScrollPane(this.input);
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 1.0;
		g.setConstraints(scroll, c);
		panel.add(scroll);

		return panel;
	}

	public static void main(String[] args)
	{
		try
		{
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		}
		catch (ClassNotFoundException e)
		{
			e.printStackTrace();
		}
		catch (InstantiationException e)
		{
			e.printStackTrace();
		}
		catch (IllegalAccessException e)
		{
			e.printStackTrace();
		}
		catch (UnsupportedLookAndFeelException e)
		{
			e.printStackTrace();
		}

		SwingUtilities.invokeLater(new Runnable() {
			public void run()
			{
				new Window().setVisible(true);
			}
		});
	}
}
