import swaggerJSDoc from 'swagger-jsdoc';

const swaggerDefinition = {
  openapi: '3.0.0',
  info: {
    title: 'Nostr Search Egnine API',
    version: '1.0.0',
    description: 'A simple API for search users of Nostr protocol',
  },
  servers: [
    {
      url: 'http://localhost:3000', // URL base da API
    },
  ],
};

const options = {
  swaggerDefinition,
  apis: ['./src/app/api/**/*.ts'], // Local onde estão os endpoints
};

const swaggerSpec = swaggerJSDoc(options);

export default swaggerSpec;

