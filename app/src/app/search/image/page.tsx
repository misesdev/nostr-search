import { Suspense } from 'react';
import LoadingImage from './loading';
import SearchImages from '@/components/SearchImages';
import { SearchParams } from '@/types/types';
import { defaultPubkey } from '@/constants';

const ImageSearchPage = async ({ searchParams }: { searchParams: SearchParams }) => {

    const pubkey = searchParams.pubkey ?? defaultPubkey;
    const searchTerm = searchParams.searchTerm;

    return (
        <Suspense fallback={<LoadingImage />}>
            <SearchImages pubkey={pubkey} searchTerm={searchTerm} />
        </Suspense>
    )    
}

export default ImageSearchPage
