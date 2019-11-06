# Projeto 3 - CUDA - Supercomp 2019.2
### Frederico Curti

O Relatório encontra-se no arquivo [relatorio.ipynb](./relatorio.ipynb)

#### Compilando
Para compilar o projeto do zero, clone o repositório e execute os seguintes comandos:

```
$ cd build
$ rm -rf *
$ cmake .. && make
```

#### Testes
Para rodar os testes e entender a dinâmica dos mesmos, basta seguir o procedimento demonstrado na sessão *BENCHMARK*, presente no relatório. Em suma, basta adicionar os arquivos de entrada no formato especificado no diretório `input` e adicioná-los à lista INPUTS no código.

- Além disso, é necessário uma instalação do CUDA SDK, e como meu computador não possui uma GPU nVidia, os testes são executados remotamente por SSH em uma instância preparada AWS, com auxilio de uma biblioteca em python chamada `paramiko`

Para instalá-la, basta usar:
```
$ pip install paramiko
```

E no código, é necessário substituir o valor da variável IP e apontar o caminho relativo do arquivo que contem a chave privada (eg. `key.pem`)
