import { ReactNode } from 'react';
import { User } from '@/types/types';
import { ImageItem } from '../images/ImageItem';

type Props = {
    results: User[]
}

export default function ImageSearchResults({ results }: Props): ReactNode {

    return (
        <div className='sm:pb-24 pb-40 m-12'>
            <div className='grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 px-3 gap-4'>
                {
                    results.map((result: User) => <ImageItem key={result.pubkey} user={result} />)
                }
            </div>
            <div className='h-12'></div>
        </div>
    );
}
