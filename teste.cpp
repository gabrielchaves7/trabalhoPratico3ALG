int max(int a, int b) { return (a > b) ? a : b; }
 
// Returns the maximum value that
// can be put in a knapsack of capacity W
int knapSack(int limiteTempo, int limiteSequencia, int tempos[], int precos[], int n)
{
 
    // Base Case
    if (n == 0 || limiteTempo == 0)
        return 0;
 
    // If weight of the nth item is more
    // than Knapsack capacity W, then
    // this item cannot be included
    // in the optimal solution
    if (tempos[n - 1] > limiteTempo)
        return knapSack(limiteTempo, limiteSequencia, tempos, precos, n - 1);
 
    // Return the maximum of two cases:
    // (1) nth item included
    // (2) not included
    else
        return max(
            precos[n - 1]
                + knapSack(limiteTempo - tempos[n - 1], limiteSequencia,
                           tempos, precos, n - 1),
            knapSack(limiteTempo, limiteSequencia, tempos, precos, n - 1));
}
 
// Driver code
int main()
{
    int precos[qtdEscalas];
    int tempos[qtdEscalas];
    for(int i =0; i <vetorEscalas.size(); i++){
        precos[i] = vetorEscalas.at(i).preco;
        tempos[i] = vetorEscalas.at(i).tempo;
    }
    int posPromocaoAtual = 1;

    cout << "--------------- \n";
	cout << knapSack(limiteTempo, limiteSequencia, tempos, precos, qtdEscalas);
    cout << "--------------- \n";
    return 0;
}