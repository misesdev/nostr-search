import { ReactNode } from 'react';
import Link from 'next/link';

const Footer = (): ReactNode => {
    return (
        <footer className='bg-gray-800 absolute bottom-0 mt-4 text-sm text-gray-500 w-full'>
            <div className='m-0 px-8 py-3 inline-flex'>
                <Link href="https://find.nosbook.org" 
                    className='text-gray-400 mx-2'
                    target='_blank'
                >
                    API documentation
                </Link>
            </div>
        </footer>
    );
}

export default Footer



