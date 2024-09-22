'use client';

import { useEffect } from 'react';

export default function Error({ error, reset }: any) {
    useEffect(() => {
        console.log('error', error);
    }, [error]);
    return (
        <div className='flex flex-col justify-center items-center pt-10'>
            <h1 className='text-[20pxl b:text-3xl mb-4 text-gray-400'>Something went wrong!</h1>
            <button className='text-blue-500'>Try again</button>
        </div>
    );
}
