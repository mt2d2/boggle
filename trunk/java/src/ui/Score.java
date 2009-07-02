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

		message.append(MessageFormat.format("You have a final score of {0}.\n", this.computeScore()));
		message.append(MessageFormat.format("You guessed {0,choice,0#0 words|1# 1 word|1<{0} words} correctly.\n", this.correct.size()));
		message.append(MessageFormat.format("  [{0}]\n", join(this.correct, " ")));
		message.append(MessageFormat.format("You guessed {0,choice,0#0 words|1# 1 word|1<{0} words} incorrectly.\n", this.incorrect.size()));
		message.append(MessageFormat.format("  [{0}]\n", join(this.incorrect, " ")));
		this.allWords.removeAll(this.correct);
		message.append(MessageFormat.format("You did not guess {0} {0,choice,0#words|1#word|1<words}.\n", this.allWords.size()));
		message.append(MessageFormat.format("  [{0}]\n", join(this.allWords, " ")));

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
