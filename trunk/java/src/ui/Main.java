package ui;

import java.util.logging.Logger;

import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class Main
{
	private static Logger logger = Logger.getLogger("bogle");
	private static final boolean IS_MAC = System.getProperty("os.name").toLowerCase().startsWith("mac os x");

	public static void main(String[] args)
	{
		try
		{
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());

			if (IS_MAC)
				System.setProperty("apple.laf.useScreenMenuBar", "true");
		}
		catch (ClassNotFoundException e)
		{
			logger.throwing("Client", "main", e);
		}
		catch (InstantiationException e)
		{
			logger.throwing("Client", "main", e);
		}
		catch (IllegalAccessException e)
		{
			logger.throwing("Client", "main", e);
		}
		catch (UnsupportedLookAndFeelException e)
		{
			logger.throwing("Client", "main", e);
		}

		SwingUtilities.invokeLater(new Runnable() {
			public void run()
			{
				new Window().setVisible(true);
			}
		});
	}
}
