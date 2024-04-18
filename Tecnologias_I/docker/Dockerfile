FROM nginx:latest

WORKDIR /app

COPY pagina.html /app
COPY styles.css /app

EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]

