### Combination Sum:
Dado um valor target N e um array com M numeros, quero contar de quantas formas consigo escrever N somando esses numeros.

```cpp
arr[3] = [1,2,3]
N = 3

Possibilidades = {
	1 + 1 + 1 
	1 + 2
	3
}

Ans = 3
```

A ideia é termos a DP(i) com o significado: 
* o numero de vezes que conseguimos formar i
```cpp
dp[0] = 1
dp[1] = 1
dp[2] = 2 => {
	1 + 1,
	2
}

entao a ideia é : 
for(int i = 1; i <= N; i++){
	for(int num: arr){
		if(i - num >= 0){
			dp[i] += dp[i-num];	 
		}		
	}
}


ou podemos ter tambem:
for(int i = 0; i <= N-1; i++){
	for(int num: arr){
		if(i + num <= N){
			dp[i+num] += dp[i];
		}
	}
}
```

### Coin Change
Dado um numero de moedas e um valor target N, qual o menor numero de moedas que conseguimos usar ? 
Uma ideia parecida, mas nesse caso, vamos guardar na dp(i) a menor quantidade de moedas que podemos usar para chegar em i.
```cpp
moedas = [1,3,4];
N = 6
dp[0] = 0;
dp[1] = 1
dp[2] = 2;
dp[3] = 1

ou seja 
dp[i] = dp[i - moeda] + 1
for(int i = 1; i <= N; i++){
	for(int moeda : moedas){
		dp[i] += min(dp[i], dp[i-moeda] + 1);
	}
}

nesse caso vale lembrar que dp[N] deve ser inicializado com infinito.
```
