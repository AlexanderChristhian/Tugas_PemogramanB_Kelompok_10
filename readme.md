
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
    make (opsional, untuk mengcompile semua file C sekaligus)
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
gcc ./src/dataset_generator.c -o ./src/dataset_generator -lm
gcc ./src/break_even_analysis.c -o ./break_even_analysis -lm
gcc ./src/main.c -o main
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


## Model Matematika

### Fungsi Pendapatan

![](https://latex.codecogs.com/svg.image?$R(x)=ax-bx^3$)

- a: Koefisien pendapatan linear (harga per unit)

- b: Koefisien penurunan pendapatan

- x: jumlah unit yang diproduksi/dijual

### Fungsi Biaya

![](https://latex.codecogs.com/svg.image?$C(x)=cx^2&plus;de^{0.01x}&plus;e$)

- c: Koefisien biaya kuadratik

- d: Koefisien biaya variabel

- e: biaya tetap

### Break Even Point

Break Even Point terjadi ketika:


![](https://latex.codecogs.com/svg.image?$R(x)=C(x)$)

atau juga bisa didefinisikan sebagai;

![](https://latex.codecogs.com/svg.image?$ax-bx^3=cx^2&plus;de^{0.01x}&plus;e$)

![](https://latex.codecogs.com/svg.image?-bx^3-cx^2&plus;ax-de^{0.01x}-e=0)

<div align="justify">
Karena persamaan ini berbentuk kuadratik, mungkin terdapat dua titik impas yang menandakan rentang operasi yang menguntungkan di antara kedua titik tersebut.
</div>

## Program Explanations

Program akan menciptakan dataset untuk setiap koefisien dengan keterangan berikut:

- a: nilai acak antara 200-300 (tingkat pendapatan yang tinggi)

- b: nilai acak antara 0.0005-0.0011 (tingkat penurunan yang rendah)

- c: nilai acak antara 0.10-0.25 (kenaikan biaya yang lebih curam)

- d:  nilai acak antara 100-200 (biaya variabel eksponensial yang wajar)
- e: nilai acak antara 2000-5000 (biaya tetap yang moderat)

Parameter ini dipilih untuk mensimulasikan skenario bisnis yang realistis dengan:

- Pendapatan awal yang tinggi namun menurun seiring peningkatan kuantitas

- Pendapatan yang menurun drastis ketika terjadi oversupply (harga menurun)

- Biaya variabel yang meningkat secara eksponensial

- Biaya tetap yang moderat

- Kompleksitas operasional yang meningkat secara kuadratik

## Tim Pengembang

|             Nama             |     NPM    | Github |
|:----------------------------:|:----------:|:------:|
|     Adrian Dika Darmawan     | 2306250711 |    [adriandikad2](https://github.com/adriandikad2)    |
|     Alexander Christhian     | 2306267025 |    [AlexanderChristian](https://github.com/AlexanderChristhian)     |
|    Ganendra Garda Pratama    | 2306250642 |    [GanendrPratama](https://github.com/GanendrPratama)    |
|    Muhammad Nadzhif Fikri    | 2306250642 |   [Kutukobra](https://github.com/Kutukobra)    |
| Muhammad Riyan Satrio Wibowo | 2306229323 |     [r-ediewitsch](https://github.com/r-ediewitsch)  |