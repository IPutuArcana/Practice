#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mahasiswa
{
    long long int nim;
    char nama[50];
    int thnMasuk;
    float IPK;
};

int jmlMhs = 0;
struct Mahasiswa *mhs;
FILE *fl;

void loaddat()
{
    fl = fopen("C:\\New folder\\modul 2\\Book1.CSV", "r");
    if (fl == NULL)
    {
        printf("File not found or unable to open.\n");
        return;
    }

    char line[2048];
    fgets(line, sizeof(line), fl); // Skip the header
    while (fgets(line, sizeof(line), fl) != NULL)
    {
        sscanf(line, "%lld,%49[^,],%d,%f", &mhs[jmlMhs].nim, mhs[jmlMhs].nama, &mhs[jmlMhs].thnMasuk, &mhs[jmlMhs].IPK);
        jmlMhs++;
    }

    fclose(fl);
}

void addData()
{
	fl = fopen("C:\\New folder\\modul 2\\Book1.CSV", "a"); // Open file in append mode

if (fl == NULL)
    {
        printf("File not found or unable to open.\n");
        return;
    }

    
    printf("Masukkan data Mahasiswa:\n");
    printf("NIM: ");
    scanf("%lld", &mhs[jmlMhs].nim);
    printf("Nama: ");
    getchar(); // Clearing the input buffer
    fgets(mhs[jmlMhs].nama, sizeof(mhs[jmlMhs].nama), stdin);
    strtok(mhs[jmlMhs].nama, "\n"); // Removing the newline character
    printf("Tahun masuk: ");
    scanf("%d", &mhs[jmlMhs].thnMasuk);
    printf("IPK: ");
    scanf("%f", &mhs[jmlMhs].IPK);

    
    

    fprintf(fl, "%lld,%s,%d,%.2f\n", mhs[jmlMhs].nim, mhs[jmlMhs].nama, mhs[jmlMhs].thnMasuk, mhs[jmlMhs].IPK);
    fclose(fl);

    jmlMhs++;
}

void viewData()
{
    fl = fopen("C:\\New folder\\modul 2\\Book1.CSV", "r");
    if (fl == NULL)
    {
        printf("File not found or unable to open.\n");
        return;
    }

    char line[2048];
    while (fgets(line, sizeof(line), fl) != NULL)
    {
        printf("%s", line);
    }

    fclose(fl);
}

void ChData()
{
    long long int nim;
    printf("Masukkan NIM Mahasiswa yang ingin diubah: ");
    scanf("%lld", &nim);

    // Buka file untuk membaca dan menulis
    FILE *temp = fopen("C:\\New folder\\modul 2\\temp.CSV", "w");
    fl = fopen("C:\\New folder\\modul 2\\Book1.CSV", "r");

    if (fl == NULL || temp == NULL)
    {
        printf("File not found or unable to open.\n");
        return;
    }

    int found = 0;
    char line[2048];

    // Baca setiap baris dari file
    while (fgets(line, sizeof(line), fl) != NULL)
    {
        long long int current_nim;
        sscanf(line, "%lld", &current_nim);

        // Jika NIM di baris ini sesuai dengan yang ingin diubah
        if (current_nim == nim)
        {
            // Mintalah input baru
            printf("Masukkan data baru untuk Mahasiswa dengan NIM %lld:\n", nim);
            printf("Nama: ");
            getchar(); // Clearing the input buffer
            fgets(mhs[jmlMhs].nama, sizeof(mhs[jmlMhs].nama), stdin);
            strtok(mhs[jmlMhs].nama, "\n"); // Removing the newline character
            printf("Tahun masuk: ");
            scanf("%d", &mhs[jmlMhs].thnMasuk);
            printf("IPK: ");
            scanf("%f", &mhs[jmlMhs].IPK);

            // Tulis data baru ke file temporary
            fprintf(temp, "%lld,%s,%d,%.2f\n", nim, mhs[jmlMhs].nama, mhs[jmlMhs].thnMasuk, mhs[jmlMhs].IPK);
            found = 1; // Tandai bahwa data telah ditemukan dan diubah
        }
        else
        {
            // Tulis baris yang tidak diubah ke file temporary
            fprintf(temp, "%s", line);
        }
    }

    fclose(fl);
    fclose(temp);

    // Hapus file asli dan ganti dengan file temporary
    remove("C:\\New folder\\modul 2\\Book1.CSV");
    rename("C:\\New folder\\modul 2\\temp.CSV", "C:\\New folder\\modul 2\\Book1.CSV");

    if (found)
    {
        printf("Data Mahasiswa dengan NIM %lld berhasil diubah.\n", nim);
    }
    else
    {
        printf("Mahasiswa dengan NIM %lld tidak ditemukan.\n", nim);
    }
}

void delData()
{
    long long int nim;
    printf("Masukkan NIM Mahasiswa yang ingin dihapus: ");
    scanf("%lld", &nim);

    // Cari Mahasiswa dengan NIM yang sesuai
    int i, found = 0;
    for (i = 0; i < jmlMhs; i++)
    {
        if (mhs[i].nim == nim)
        {
            // Mahasiswa ditemukan, hapus data Mahasiswa tersebut
            found = 1;
            printf("Data Mahasiswa dengan NIM %lld akan dihapus.\n", nim);
            // Geser data ke kiri untuk menutup celah
            for (int j = i; j < jmlMhs - 1; j++)
            {
                mhs[j] = mhs[j + 1];
            }
            jmlMhs--; // Kurangi jumlah Mahasiswa
            break;
        }
    }

    if (!found)
    {
        printf("Mahasiswa dengan NIM %lld tidak ditemukan.\n", nim);
        return;
    }

    // Tulis kembali seluruh data ke file setelah penghapusan dilakukan
    fl = fopen("C:\\New folder\\modul 2\\Book1.CSV", "w");
    if (fl == NULL)
    {
        printf("File not found or unable to open.\n");
        return;
    }

    // Tulis header
    fprintf(fl, "NIM, Nama, Tahun masuk, IPK\n");

    // Tulis data Mahasiswa
    for (int j = 0; j < jmlMhs; j++)
    {
        fprintf(fl, "%lld,%s,%d,%.2f\n", mhs[j].nim, mhs[j].nama, mhs[j].thnMasuk, mhs[j].IPK);
    }

    fclose(fl);
    printf("Data Mahasiswa dengan NIM %lld berhasil dihapus.\n", nim);
}

void sData()
{
    long long int searchNIM;
    printf("Masukkan NIM Mahasiswa yang ingin dicari: ");
    scanf("%lld", &searchNIM);

    int found = 0;
    for (int i = 0; i < jmlMhs; i++)
    {
        if (mhs[i].nim == searchNIM)
        {
            printf("\nData Mahasiswa dengan NIM %lld:\n", searchNIM);
            printf("Nama: %s\n", mhs[i].nama);
            printf("Tahun Masuk: %d\n", mhs[i].thnMasuk);
            printf("IPK: %.2f\n", mhs[i].IPK);
            found = 1;
            break; // Keluar dari loop karena sudah menemukan Mahasiswa yang dicari
        }
    }
    if (!found)
    {
        printf("\nMahasiswa dengan NIM %lld tidak ditemukan.\n", searchNIM);
    }

    getchar(); // Menunggu pengguna menekan Enter
}

    

int main()
{
    mhs = (struct Mahasiswa *)malloc(100 * sizeof(struct Mahasiswa)); // Initial memory allocation

    loaddat();

    int menu;
    do
    {
        printf("Menu");
        printf("\n1. Add data");
        printf("\n2. Display data");
        printf("\n3. Change the data");
        printf("\n4. Erease data");
        printf("\n5. Search");
        printf("\n6. Exit");
        printf("\nChoose menu: ");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            addData();
            break;
        case 2:
            viewData();
            break;
        case 3:
        	ChData();
        	break;
        case 4:
        	delData();
        	break;
        case 5:
        	sData();
        	break;
        case 6:
            printf("Exiting program.\n");
            return 0;
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }

    } while (menu != 6);

    free(mhs); // Free allocated memory
    return 0;
}

