package game;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.swing.JOptionPane;

public class Lexicon implements Iterable<String>
{
	private List<String> dictionary;
	private List<String> lexicon;

	public Lexicon()
	{
		this.dictionary = new ArrayList<String>();
		this.lexicon = new ArrayList<String>();

		((ArrayList<String>)this.dictionary).ensureCapacity(81055);
		((ArrayList<String>)this.lexicon).ensureCapacity(81055);

		this.load();
	}

	public void filter(String pattern)
	{
		this.lexicon.clear();

		Pattern p = Pattern.compile('[' + pattern + "]+");

		for (String s : this.dictionary)
		{
			Matcher m = p.matcher(s);

			if (m.matches())
				this.lexicon.add(s);
		}
	}

	public boolean hasWord(String word)
	{
		return (Collections.binarySearch(this.lexicon, word) >= 0);
	}

	private void load()
	{
		try
		{
			BufferedReader reader = new BufferedReader(new InputStreamReader(this.getClass().getResourceAsStream("dictionary.txt")));
			String line = null;
			while ((line = reader.readLine()) != null)
				this.dictionary.add(line);
		}
		catch (Exception e)
		{
			JOptionPane.showMessageDialog(null, "A fatal error in loading the dictionary has prevented the application from launching.");
			System.exit(-1);
		}
	}

	@Override
	public Iterator<String> iterator()
	{
		return this.lexicon.iterator();
	}
}
