
<div align="center">
    <h1>
        Break-even Analysis dalam Model Biaya-Pendapatan Non-Linear 
    </h1>
</div>


## Deskripsi Proyek

<div align="justify">
Proyek ini mengimplementasi analisis break-even point pada model biaya dan pendapatan non-linear menggunakan metode numerik. Dengan menggunakan metode Secant untuk mencari titik impas (Break Even Point).

Implementasi dilakukan dalam bahasa C dengan visualisasi menggunakan GNUplot.
</div>

## Instalasi dan Kompilasi

<details open>
    <summary> Prerequisites </summary>
    <li> 
    GCC (compiler C)
    </li>
    <li>
    cmake (opsional, untuk mengcompile semua file C sekaligus)
    </li>
    <li>
    Gnuplot (untuk visualisasi hasil)
    </li>
    <li>
    Git (untuk clone repository)
    </li>
</details>

<br>

<details open>
    <summary> Clone Repository </summary>

```console

# Using HTTPS
git clone https://github.com/AlexanderChristhian/Tugas_PemogramanB_Kelompok_10.git

# Using ssh
git clone git@github.com:AlexanderChristhian/Tugas_PemogramanB_Kelompok_10.git

# Change directory to project directory
cd Tugas_PemogramanB_Kelompok_10

```
</details>

<details open>

<summary> File Compilation </summary>

* Using `make`

```console
make
```

* Manual compilation

```console
gcc src/dataset_generator.c -o dataset_generator -lm
gcc src/break_even_analysis.c -o break_even_analysis -lm
gcc src/main.c -o main
```

</details>

<details open>

<summary> Executing the File </summary>

On Windows
```console
cd src
./main.exe
```

On Linux
```console
cd src
./main
```

</details>


## 


## Tim Pengembang

|             Nama             |     NPM    | Github |
|:----------------------------:|:----------:|:------:|
|     Adrian Dika Darmawan     | 2306250711 |    [adriandikad2](https://github.com/adriandikad2)    |
|     Alexander Christhian     | 2306267025 |    [AlexanderChristian](https://github.com/AlexanderChristhian)     |
|    Ganendra Garda Pratama    | 2306250642 |    [GanendrPratama](https://github.com/GanendrPratama)    |
|    Muhammad Nadzhif Fikri    | 2306250642 |   [Kutukobra](https://github.com/Kutukobra)    |
| Muhammad Riyan Satrio Wibowo | 2306229323 |     [r-ediewitsch](https://github.com/r-ediewitsch)  |