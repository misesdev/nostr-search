
FROM node:latest

WORKDIR /var/html/app

COPY . .

RUN npm install

RUN npm run build 

CMD ["npm", "run", "start"]



