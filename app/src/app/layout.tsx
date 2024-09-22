import './globals.css';
import Footer from '@/components/Footer';

export const metadata = {
    title: 'Nosbook - Search on Nostr',
    description: 'A search engine for Nostr.',
};

export default function RootLayout({ children }: any) {
    return (
        <html lang='en' className="bg-gray-900">
            <head>
                <meta name="viewport" content="width=device-width, initial-scale=1.0" />
            </head>
            <body className='bg-gray-900 bg-gradient-to-b relative min-h-screen'>
                {children}
                <Footer />
            </body>
        </html>
    );
}


