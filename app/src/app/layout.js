import './globals.css';
import Footer from '@/components/Footer';

export const metadata = {
    title: 'Noogle',
    description: 'An open source search engine for Nostr.',
};

export default function RootLayout({ children }) {
    return (
        <html lang='en' className="bg-gray-900">
            <body className='bg-gray-900 bg-gradient-to-b relative min-h-screen'>
                {children}
                <Footer />
            </body>
        </html>
    );
}


