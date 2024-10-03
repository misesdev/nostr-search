import { NextResponse } from 'next/server';
import swaggerUi from 'swagger-ui-express';
import swaggerSpec from '@/../swagger'; // ajuste o caminho conforme necessário

export async function GET() {
    const swaggerHtml = swaggerUi.generateHTML(swaggerSpec);

    return new NextResponse(swaggerHtml, {
        headers: {
            'Content-Type': 'text/html',
        },
    });
}


