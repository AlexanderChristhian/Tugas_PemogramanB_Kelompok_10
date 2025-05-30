
<div align="center">
    <h1>
        Break-even Analysis dalam Model Biaya-Pendapatan Non-Linear 
    </h1>
</div>


## Deskripsi Proyek

<div align="justify">
Proyek ini mengimplementasi analisis break-even point pada model biaya dan pendapatan non-linear menggunakan metode numerik. Dengan menggunakan metode Secant untuk mencari titik impas (Break Even Point).

Implementasi dilakukan dalam bahasa C dan divisualisasikan menggunakan GNUplot.
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

<summary> Generating Dataset </summary>

On Windows
```console
cd src
./dataset_generator.exe
```

On Linux
```console
cd src
./dataset_generator
```

</details>

<details open>

<summary> Executing the Dataset and Plotting with gnuplot </summary>

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

### Fungsi Pendapatan

$$
R(x) = ax - bx^3
$$

| Simbol | Keterangan                          |
|--------|-------------------------------------|
| a      | Koefisien pendapatan linear (harga per unit) |
| b      | Koefisien penurunan pendapatan      |
| x      | Jumlah unit yang diproduksi/dijual  |


### Fungsi Biaya

$$
C(x) = cx^2 + de^{0.01x} + e
$$

| Simbol | Keterangan                          |
|--------|-------------------------------------|
| c      | Koefisien biaya kuadratik           |
| d      | Koefisien biaya variabel            |
| e      | Biaya tetap                         |

### Break Even Point

Break Even Point terjadi ketika:

$$
ax - bx^3 = cx^2 + de^{0.01x} + e
$$

Atau disusun ulang menjadi:

$$
{- bx^3 - cx^2 + ax - de^{0.01x} - e = 0}
$$

| Simbol | Keterangan                          |
|--------|-------------------------------------|
| a      | Koefisien pendapatan linear         |
| b      | Koefisien penurunan pendapatan      |
| c      | Koefisien biaya kuadratik           |
| d      | Koefisien biaya variabel            |
| e      | Biaya tetap                         |


<div align="justify">
Karena persamaan ini berbentuk kuadratik, mungkin terdapat dua titik impas yang menandakan rentang operasi yang menguntungkan di antara kedua titik tersebut.
</div>

## Program Explanations

### Dataset

Program menciptakan sejumlah dataset untuk setiap koefisien dengan nilai acak dalam rentang serta keterangan berikut:

<table>
<tr>
    <th rowspan="2">
        Koefisien
    </th>
    <th colspan="2">
        Rentang
    </th>
    <th rowspan="2">
        Keterangan
    </th>
</tr>
<tr>
    <td>
        Min.
    </td>
    <td>
        Maks.
    </td>
</tr>
<tr>
    <td>
        a
    </td>
    <td>
        200 
    </td>
    <td>
        300
    </td>
    <td>
        tingkat pendapatan yang tinggi
    </td>
</tr>
<tr>
    <td>
        b
    </td>
    <td>
        0.0005
    </td>
    <td>
        0.0011
    </td>
    <td>
        tingkat penurunan yang rendah
    </td>
</tr>
<tr>
    <td>
        c
    </td>
    <td>
        0.10 
    </td>
    <td> 
        0.25
    </td>
    <td>
        kenaikan biaya yang lebih curam
    </td>
</tr>
<tr>
    <td>
        d
    </td>
    <td>
        100 
    </td>
    <td> 
        200
    </td>
    <td>
        biaya variabel eksponensial yang wajar
    </td>
</tr>
<tr>
    <td>
        e
    </td>
    <td>
        2000 
    </td>
    <td> 
        5000
    </td>
    <td>
        biaya tetap yang moderat
    </td>
</tr>
</table>


Parameter ini dipilih untuk mensimulasikan skenario bisnis yang realistis dengan:
- Pendapatan awal yang tinggi namun menurun seiring peningkatan kuantitas

- Pendapatan yang menurun drastis ketika terjadi oversupply (harga menurun)

- Biaya variabel yang meningkat secara eksponensial

- Biaya tetap yang moderat

- Kompleksitas operasional yang meningkat secara kuadratik

Program `dataset_generator.c` menciptakan dataset menggunakan rand() serta srand() yang menggunakan seed acak ataupun dapat dispesifikasikan dalam CLI menggunakan `./dataset_generator [SEED]`.

Koefisien diciptakan dengan sebuah fungsi `generateCoefficients()` 
```c
void generateCoefficients(double *a, double *b, double *c, double *d, double *e) {
    // Revenue coefficients (R(x) = a*x - b*x^3)
    *a = 200 + (rand() % 101); 
    *b = 0.0005 + (rand() % 6)/10000.0; 
    
    // Cost coefficients (C(x) = c*x^2 + d*exp(0.01x) + e)
    *c = 0.10 + (rand() % 15)/100.0; 
    *d = 100 + (rand() % 101); 
    *e = 2000 + (rand() % 3001); 
}
```

Sehingga dapat dituliskan ke dalam sebuah file `dataset.txt` 
```c
fp = fopen("dataset.txt", "w");
...
generateCoefficients(&a, &b, &c, &d, &e);
...
fprintf(fp, "%.2f %.4f %.2f %.2f %.2f\n", a, b, c, d, e);

```

### Break-Even Analysis

Program `break_even_analysis.c` membaca setiap koefisien yang telah diciptakan dalam `dataset.txt` untuk diproses menggunakan metode secant.

```c
double a, b, c, d, e;
if (fscanf(input, "%lf %lf %lf %lf %lf", &a, &b, &c, &d, &e) != 5) {
    printf("Error reading dataset %d\n", i);
    continue;
}
processDataset(i, a, b, c, d, e);
```

Koefisien diolah menggunakan fungsi `processDataset()` yang menerima indeks dataset serta setiap koefisien. 

## Tim Pengembang

|             Nama             |     NPM    | Github |
|:----------------------------:|:----------:|:------:|
|     Adrian Dika Darmawan     | 2306250711 |    [adriandikad2](https://github.com/adriandikad2)    |
|     Alexander Christhian     | 2306267025 |    [AlexanderChristian](https://github.com/AlexanderChristhian)     |
|    Ganendra Garda Pratama    | 2306250642 |    [GanendrPratama](https://github.com/GanendrPratama)    |
|    Muhammad Nadzhif Fikri    | 2306250642 |   [Kutukobra](https://github.com/Kutukobra)    |
| Muhammad Riyan Satrio Wibowo | 2306229323 |     [r-ediewitsch](https://github.com/r-ediewitsch)  |