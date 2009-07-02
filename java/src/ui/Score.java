package ui;

import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

public class Score
{
	private List<String> allWords;
	private List<String> correct;
	private List<String> incorrect;

	public Score(List<String> allWords)
	{
		this.allWords = allWords;
		this.correct = new ArrayList<String>();
		this.incorrect = new ArrayList<String>();
	}

	public String score(String input)
	{
		List<String> inputs = split(input);

		for (String s : inputs)
		{
			if (this.allWords.contains(s))
				this.correct.add(s);
			else
				this.incorrect.add(s);
		}

		StringBuilder message = new StringBuilder();

		message.append(MessageFormat.format(Messages.getString("Score.finalScore"), this.computeScore())); //$NON-NLS-1$
		message.append(MessageFormat.format(Messages.getString("Score.correct"), this.correct.size())); //$NON-NLS-1$
		message.append(MessageFormat.format(Messages.getString("Score.listFormat"), join(this.correct, " "))); //$NON-NLS-1$
		message.append(MessageFormat.format(Messages.getString("Score.incorrect"), this.incorrect.size())); //$NON-NLS-1$
		message.append(MessageFormat.format(Messages.getString("Score.listFormat"), join(this.incorrect, " "))); //$NON-NLS-1$ //$NON-NLS-2$
		this.allWords.removeAll(this.correct);
		message.append(MessageFormat.format(Messages.getString("Score.allWords"), this.allWords.size())); //$NON-NLS-1$
		message.append(MessageFormat.format(Messages.getString("Score.listFormat"), join(this.allWords, " "))); //$NON-NLS-1$

		return message.toString();
	}

	private int computeScore()
	{
		int score = 0;

		for (String word : this.correct)
		{
			if (word.length() <= 4)
				score += 1;
			else if (word.length() == 5)
				score += 2;
			else if (word.length() == 6)
				score += 3;
			else if (word.length() >= 7 && word.length() <= 10)
				score += 5;
			else if (word.length() >= 11)
				score += 8;
		}

		for (String word : this.incorrect)
		{
			if (word.length() <= 4)
				score -= 1;
			else if (word.length() == 5)
				score -= 2;
			else if (word.length() == 6)
				score -= 3;
			else if (word.length() >= 7 && word.length() <= 10)
				score -= 5;
			else if (word.length() >= 11)
				score -= 8;
		}

		return score;
	}

	private static List<String> split(String input)
	{
		if (input == null || input.length() == 0)
			return Collections.emptyList();

		return Arrays.asList(input.split(" "));
	}

	private static String join(List<String> input, String delim)
	{
		if (input == null || input.size() == 0)
			return "";

		StringBuilder sb = new StringBuilder();

		Iterator<String> itr = input.iterator();
		sb.append(itr.next());
		while (itr.hasNext())
			sb.append(delim).append(itr.next());

		return sb.toString();

	}
}
