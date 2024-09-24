import { Suspense } from 'react';
import LoadingImage from './loading';
import ImageSearch from '@/components/search/ImageSearch';
import { SearchParams } from '@/types/types';
import { defaultPubkey } from '@/constants';

const ImageSearchPage = async ({ searchParams }: { searchParams: SearchParams }) => {

    const pubkey = searchParams.pubkey ?? defaultPubkey;
    const searchTerm = searchParams.searchTerm;

    return (
        <Suspense fallback={<LoadingImage />}>
            <ImageSearch pubkey={pubkey} searchTerm={searchTerm} />
        </Suspense>
    )    
}

export default ImageSearchPage
