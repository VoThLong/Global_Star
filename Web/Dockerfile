FROM node:22-alpine

RUN apk add --no-cache tzdata
ENV TZ=Asia/Ho_Chi_Minh

WORKDIR /app

COPY package*.json ./
RUN npm install --production

COPY . .

# Tạo thư mục và cấp quyền cho user node
RUN mkdir -p /app/data && chown -R node:node /app/data

EXPOSE 3000

USER node

CMD ["node", "ai_studio_code.js"]
