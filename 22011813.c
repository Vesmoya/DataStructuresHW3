/*Volkan Tayranoglu 22011813 Veri Yapilari ve Algoritmalar 3. Odev*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//max heap tree özelligine gore heapify yapan fonksiyon
void heapify(int *heapList, int cap,int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < cap && heapList[left] > heapList[largest])
        largest = left;//Queue'nun sonuna ulasilmadiysa ve sol cocuk parenttan buyukse sol cocugu parent yap

    if (right < cap && heapList[right] > heapList[largest])
        largest = right; // Queue'nun sonuna ulasilmadiysa ve sag cocuk parenttan buyukse sag çocugu parent yap

    if (largest != i) //parent degeri ayni degilse yani degistiyse yer degistirme islemi yapilir.
    {
        int temp = heapList[i];
        heapList[i] = heapList[largest];
        heapList[largest] = temp;

        heapify(heapList, cap, largest); //max heap tree ozelligi saglanana kadar devam et.
    }
}
//Heapsort algoritmasını burada baslatip heapify fonksiyonunu cagirarak devam ediyoruz.
void heapSort(int *heapList, int cap)
{
    int i;
    for (i = cap / 2; i >= 0; i--)
        heapify(heapList, cap, i);
}
//Heapify islemi sonrasinda queue'nun basina alinan en büyük elemani cikartan fonksiyon.
void extractMaxNumber(int *queue, int M)
{
    int i;
    for(i=1;i<M;i++){//Her bir eleman bir oncekinin yerine yaziyoruz. Böylelikle bastaki eleman siliniyor. 
        if(queue[i-1]!=-1){
            queue[i-1]=queue[i];
        }
    }
    queue[M-1]=-1;//Sona -1 degeri atiyoruz.
    
}
//Matrisimizi ekrana yazdirmak icin kullandigimiz fonksiyon
void printMatrix(int **matrix,int N,int M){
    int i,j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    int i,j,N,M;
    srand(time(NULL));


    printf("Matrisin boyutlarini N M seklinde giriniz:");
    scanf("%d %d", &N, &M);
    int *queueCapacities;//Queue'larin kapasitelerinin tutuldugu dizi
    int *numberList;//Random unique sayilar atilirken kullanilan sayilarin tutuldugu dizi
    int **matrix;//Matrisimiz.
    int *emptyQueues;//Bosalan queue'larin sirasini tutan dizimiz.

    matrix = (int **)malloc(N * sizeof(int *));//Bellek ayirma islemleri
    for (i = 0; i < N; i++)
    {
        matrix[i] = (int *)malloc(M * sizeof(int));
    }
    queueCapacities = (int *)malloc(N* sizeof(int));
    numberList = (int *)malloc((N*M) * sizeof(int));
    emptyQueues = (int *)malloc(N * sizeof(int));

    for (i = 0; i < N; i++) {
        printf("%d. kuyrugun kapasitesini giriniz: ", i+1);
        scanf("%d", &queueCapacities[i]);//Kullanicidan kuyruk kapasitelerini aliyoruz.
    }

    for(i = 0; i < N * M; i++){//numberList dizisine matris boyutu kadar sayi atiyoruz.
        numberList[i] = i+1;
    }

    int randomIndex,tmp;

    for (i = 0; i < N * M; i++)
    {//numberList dizisindeki degerleri rastgele sayi uretmek icin karistiriyoruz.
        randomIndex = rand() % (N * M - i);
        tmp = numberList[i];
        numberList[i] = numberList[randomIndex];
        numberList[randomIndex] = tmp;
    }

    int count=0;
    
    //Karisan numberList dizisini matrise atayarak rastgele unique sayilar elde ediyoruz.
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (j < queueCapacities[i])
            {
                matrix[i][j] = numberList[count++];
            }
            else
            {
                matrix[i][j] = -1;
            }
        }
    }

    printf("Matrisin ilk hali:\n");

    printMatrix(matrix,N,M);
    
    int notEmptyQueueCount=N;//Matrisdeki bos olmayan queue sayisini tutan degisken
    int emptyIndex = 0;//Bos olmayan queue uzerinde kullandigimiz index.
    int maxNumber=-1;//Queue baslarindaki en büyük sayiyi tutacagimiz degisken.
    int maxNumberQueueIndex;//En büyük sayiyi buldugumuz queue numarasini tutan index.

    while(notEmptyQueueCount!=0){//Butun queue'lar bosalana kadar devam et

        notEmptyQueueCount=N;//Bos olmayan queue sayisini sifirlarayak her adimda bastan sayiyoruz.
        for (i = 0; i < N; i++)
        {
            if (matrix[i][0] != -1)
            {
                heapSort(matrix[i], queueCapacities[i]); //Bastaki eleman -1 degil ise heapSort fonksiyonu ile siralama yap.
            }
            else
            {
                notEmptyQueueCount--; //Bastaki deger -1 ise bos olmayan queue sayisini azalt.
            }
            
        }
        printf("Heapify islemi sonrasi matris:\n");
        printMatrix(matrix, N, M);

        //Queue kapasitesi 0'a ulasmadiysa bastaki degeri en buyuk sayi ile karsilastir. Daha buyukse o sayiyi en buyuk sayi yap.
        for(i=0;i<N;i++){
            if(queueCapacities[i]>0){
                if(matrix[i][0]>maxNumber){
                    maxNumber=matrix[i][0];
                    maxNumberQueueIndex=i;
                }
            }
        }
        printf("Secilen eleman:%d \n",maxNumber);

        //Buldugumuz en buyuk sayiyi queue'dan cikart.
        extractMaxNumber(matrix[maxNumberQueueIndex], M);
        
        //Cikartma islemi sonrasi bastaki sayi -1 oldu ise bosalan dizi listesine Queue numarasini yaz.
        if (matrix[maxNumberQueueIndex][0]==-1)
        {
            emptyQueues[emptyIndex] = maxNumberQueueIndex + 1;
            emptyIndex++;
        }
        maxNumber=-1;//maxNumber'ı tekrar -1 yapiyoruz.

        printf("En buyuk deger ciktiktan sonraki matris:\n");

        printMatrix(matrix, N, M);
    }

    printf("Sirayla elemanlari tukenen kuyruklar: ");

    //Ekrana elemanlari tukenen kuyruklarin sirasini yazdiriyoruz.
    for(i=0;i<N;i++){
        printf("%d ",emptyQueues[i]);
    }

    //Bellek bosaltma islemleri.
    for (i = 0; i < N; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    free(queueCapacities);
    free(emptyQueues);
    free(numberList);

    return 0;
}
