package main

import (
	"fmt"
	"math/rand"
	"os"
)

func main() {
	name := "test/testdata/test_"
	for i := 0; i < 50; i++ {
		file := fmt.Sprintf("%v%v", name, i)
		f, err := os.Create(file)
		if err != nil {
			fmt.Print("error when creating file")
		}
		defer f.Close()
		number := 200
		fmt.Fprintln(f, number)
		a := make([]int, number)
		k := rand.Int() % 10
		if k == 0 {
			k = 1
		}
		fmt.Fprintln(f, k)
		for j := 0; j < number; j++ {
			a[i] = rand.Int() % 10
			fmt.Fprintf(f, "%v ", a[i])
		}
	}
}
