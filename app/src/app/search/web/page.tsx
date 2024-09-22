import { Suspense } from 'react';
import LoadingWeb from './loading';
import SearchResults from '@/components/SearchResults';
import { SearchParams } from '@/types/types';
import { defaultPubkey } from '@/constants/pubkey';

const WebSearchPage = async ({ searchParams }: { searchParams: SearchParams }) => {

    const pubkey = searchParams.pubkey ?? defaultPubkey;
    const searchTerm = searchParams.searchTerm;

    return (
        <Suspense fallback={<LoadingWeb />}>
            <SearchResults pubkey={pubkey} searchTerm={searchTerm} />
        </Suspense>
    )
}

export default WebSearchPage
