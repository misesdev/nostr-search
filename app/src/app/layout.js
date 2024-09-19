import './globals.css';
import Footer from '@/components/Footer';

export const metadata = {
    title: 'Nostr Book',
    description: 'An open source search engine for Nostr.',
};

export default function RootLayout({ children }) {
    return (
        <html lang='en'>
            <body className='relative min-h-screen'>
                {children}
                <Footer />
            </body>
        </html>
    );
}


