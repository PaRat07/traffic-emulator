import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';
import progress from 'vite-plugin-progress'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [
    progress(),
    react(),
  ],
  server: {
    host: true
  }
})
