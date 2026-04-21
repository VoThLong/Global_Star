FROM node:20-alpine

WORKDIR /app

# Copy package files
COPY package*.json pnpm-lock.yaml* ./

# Install pnpm and dependencies
RUN npm install -g pnpm && pnpm install --no-frozen-lockfile

# Copy application code
COPY . .

# Expose port
EXPOSE 3000

# Start the application
ENTRYPOINT ["node", "./ai_studio_code.js"]
