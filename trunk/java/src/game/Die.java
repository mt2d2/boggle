package game;

public class Die
{
	private char letter;
	private boolean marked;
	
	public Die(char letter)
	{
		this.letter = letter;
		this.marked = false;
	}
	
	public char getLetter()
	{
		return this.letter;
	}
	public void setLetter(char letter)
	{
		this.letter = letter;
	}
	public boolean isMarked()
	{
		return this.marked;
	}
	public void setMarked(boolean marked)
	{
		this.marked = marked;
	}
	
	@Override
	public String toString()
	{
		return Character.toString(this.letter);
	}
}
