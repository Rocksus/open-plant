package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"time"

	"github.com/gorilla/mux"
)

type Plant struct {
	ID          int64   `json:"id"`
	Temperature int     `json:"temperature"`
	Humidity    float32 `json:"humidity"`
	Moisture    float32 `json:"moisture"`
}

func PlantHandler(w http.ResponseWriter, r *http.Request) {
	decoder := json.NewDecoder(r.Body)
	var p Plant
	decoder.Decode(&p)

	w.WriteHeader(http.StatusOK)
	fmt.Println(p)
}

func main() {
	r := mux.NewRouter()

	r.HandleFunc("/plants", PlantHandler).Methods("POST")

	srv := &http.Server{
		Handler:      r,
		Addr:         "127.0.0.1:8000",
		WriteTimeout: 15 * time.Second,
		ReadTimeout:  15 * time.Second,
	}

	fmt.Println("Server started at port 8000")
	log.Fatal(srv.ListenAndServe())
}
