using System;
using System.Collections.Generic;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

public partial class Window : Form
{
	private bool running;
	private DiceTray diceTray;
	private Lexicon lexicon;
	private List<string> allWords;
	private Thread backgroundSearcher;
	private int time;
	private System.Windows.Forms.Timer timer;

	public Window()
	{
		InitializeComponent();

		// Manually create the label grid
		this.diceGrid.SuspendLayout();
		for (int i = 0; i < 16; i++)
			this.diceGrid.Controls.Add(this.makeGamePiece('-'));
		this.diceGrid.ResumeLayout();

		// other game setup
		this.timer = new System.Windows.Forms.Timer();
		this.timer.Interval = 1000;
		this.timer.Tick += new EventHandler(this.onTimerCountdown);
	}

	private void startGame()
	{
		this.gameStatus.Text = "Time remaining: 3:00";
		this.gameButton.Text = "Stop";
		this.input.Enabled = true;
		this.input.Focus();

		this.diceTray = new DiceTray();
		int count = 0;
		this.diceGrid.SuspendLayout();
		for (int row = 0; row < 4; row++)
			for (int col = 0; col < 4; col++)
				this.diceGrid.Controls[count++].Text = this.diceTray.dice[row, col].letter + "";
		this.diceGrid.ResumeLayout();

		this.allWords = new List<string>();
		this.backgroundSearcher = new Thread (this.backgroundSearch);
		this.backgroundSearcher.Start();
		this.time = 180;
		this.timer.Start();
	}

	private void stopGame()
	{
		this.timer.Stop();

		if (this.backgroundSearcher.IsAlive)
			this.backgroundSearcher.Join();

		MessageBox.Show ("Found the following words: " + String.Join (" ", this.allWords.ToArray()));

		this.gameStatus.ForeColor = Color.Black;
		this.gameStatus.Text = "Press start to begin the game...";
		this.gameButton.Text = "Start";
		this.input.Enabled = false;
		this.gameButton.Focus();

		this.diceTray = null;
		int count = 0;
		this.diceGrid.SuspendLayout();
		for (int row = 0; row < 4; row++)
			for (int col = 0; col < 4; col++)
				this.diceGrid.Controls[count++].Text = "-";
		this.diceGrid.ResumeLayout();

		this.allWords = null;
	}

	private void gameButton_Click (object sender, EventArgs e)
	{
		if (this.running)
			this.stopGame();
		else
			this.startGame();

		this.running = !this.running;
	}


	private void onTimerCountdown (Object source, EventArgs myEventArgs)
	{
		if (this.time == 0) 
		{
			this.stopGame();
			return;
		}

		this.time--;

	 	string minutes = time / 60 + "";
		int mod = time % 60;
		string seconds = (mod < 10) ? ("0" + mod) : ("" + mod); 

		this.gameStatus.Text = "Time remaining: " + minutes + ":" + seconds;

		if (this.time <= 60)
			this.gameStatus.ForeColor = Color.Red;
	}

	private void backgroundSearch()
	{
		if (this.lexicon == null)
			this.lexicon = new Lexicon("dictionary.txt");

		this.lexicon.filterLexicon(this.diceTray.ToPattern());

		foreach (string s in this.lexicon)
			if (this.diceTray.stringFound(s))
				this.allWords.Add(s);
	}

	private Label makeGamePiece (char text)
	{
		Label l = new Label();

		l.Text = "" + text;
		l.TextAlign = ContentAlignment.MiddleCenter;
		l.Font = new Font (l.Font.FontFamily, 18, FontStyle.Bold);

		return l;
	}
}
