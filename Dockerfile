FROM golang:1.12 AS build

# Environment variables will be put here
ENV GO111MODULE=on


# end

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y git

WORKDIR /go/src/open-plant/

COPY go.mod go.sum ./
RUN go mod download

COPY . .
RUN pwd && \
    ls

RUN go test ./...

RUN CGO_ENABLED=0 GOOS=linux GOARCH=amd64 go build -ldflags="-w -s" -o main ./cmd

FROM alpine
COPY --from=build /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/
COPY --from=build /go/src/open-plant/main go/bin/open-plant/
RUN ls

EXPOSE 8000
WORKDIR go/bin/open-plant/

CMD ["./main"]