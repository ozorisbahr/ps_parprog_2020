// mergesort-sections.c
#pragma omp parallel sections
{
#pragma omp section
{
mergesort_parallel_omp (a, size / 2, temp, threads / 2);
}
#pragma omp section
{
mergesort_parallel_omp (a + size / 2, size - size / 2,
temp + size / 2, threads - threads / 2);
}
}
merge(a, size, temp);