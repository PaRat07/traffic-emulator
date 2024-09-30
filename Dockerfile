FROM node:19-alpine

RUN mkdir app

WORKDIR /app

COPY package.json package-lock.json ./

RUN npm install && export NODE_OPTIONS="--max-old-space-size=8192"

COPY . .

EXPOSE 5173

CMD npm run dev
