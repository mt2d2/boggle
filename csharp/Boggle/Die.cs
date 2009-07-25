class Die
{
    public bool marked { get; set; }
    public char letter { get; set; }

    public Die(char letter)
    {
        this.letter = letter;
        this.marked = false;
    }

    public override string ToString()
    {
        return this.letter + "";
    }
}

