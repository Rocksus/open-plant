FROM golang:1.12-alpine AS build

# Environment variables will be put here



# end

WORKDIR /go/src/open-plant/

COPY go.mod .
COPY go.sum .
RUN go mod download

COPY . /go/src/open-plant
RUN go test ./...

RUN go build cmd -o /bin/open-plant

FROM scratch

COPY --from=build /go/bin/open-plant/main /app/
WORKDIR /app

EXPOSE 8080

CMD ["./main"]
